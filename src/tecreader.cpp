#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#ifdef _WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

namespace po = boost::program_options;
namespace asio = boost::asio;
using namespace std;


int main(int argc, char *argv[]){
    string serialPortName;
    const unsigned int& baud_rate = 9600;
    stringstream infoText;
    asio::io_service io;
    po::options_description desc("Options");
    desc.add_options() 
      ("help,h", "Print help messages")
      ("port,p", po::value<string>()->required(), "specify comport - i.e.: COM1 | /dev/ttyS0");
    po::variables_map vm;
    //po::store(po::parse_command_line(argc, argv, desc), vm);
    po::parsed_options parsed =
        po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
    vector<string> CMD = collect_unrecognized(parsed.options, po::include_positional);

    infoText << "Basic Command Line Parameter Arguments" << desc;

    if ( vm.count("help")  ) 
    {
        std::cout << infoText.str();
        return 0;
    }

    if ( vm.count("port") )
    {
        serialPortName = vm["port"].as<string>();
    }

    try // check if all required commandline parameters are set
    {
        po::notify(vm);
    }
    catch(po::error& e)
    {
        std::cout  << "missing parameter for port!" << std::endl << std::endl << infoText.str();
        return 1;
    }

    // format the command string for the serial interface
    stringstream CMDstream;
    for (int i=0; i<CMD.size(); i++)
    {
        if (i<CMD.size()-1)
        {
            CMDstream << CMD[i] << " ";
        } else {
        CMDstream << CMD[i] << std::endl;
        }
    }

    asio::serial_port serialPort(io);
    int i = 1;
    while (i < 20)
    {
        try
        {
            serialPort.open(serialPortName);
            break;
        }
        catch (exception& e)
        {
            if (i == 19)
            {
                cout << "Standard exception: " << e.what() << endl;
                return 1;
            }
            Sleep(500);
            i++;
        }
    }

    serialPort.set_option(asio::serial_port::baud_rate(baud_rate));
    asio::write(serialPort, asio::buffer(CMDstream.str()));
    asio::streambuf response;
    asio::read_until(serialPort, response, "\r\n");
    std::istream response_stream(&response);
    string responsestr;
    getline(response_stream, responsestr);
    char unwanted_chars[] = "+ ";
    for (int i = 0; i < strlen(unwanted_chars); ++i)
    {
        responsestr.erase(remove(responsestr.begin(), responsestr.end(), unwanted_chars[i]), responsestr.end());
    }
    cout << responsestr;

    return 0;
}
