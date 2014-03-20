#include <iostream>
#include <string>
//#include <vector>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>

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

    asio::serial_port serialPort(io, serialPortName);
    serialPort.set_option(asio::serial_port::baud_rate(baud_rate));
    asio::write(serialPort, asio::buffer(CMDstream.str()));
    asio::streambuf response;
    asio::read_until(serialPort, response, "\r\n");
    std::istream response_stream(&response);
    string responsestr;
    response_stream >> responsestr;
    cout << responsestr;

    return 0;
}

