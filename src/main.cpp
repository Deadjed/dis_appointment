#include <iostream>         // Console in/out
#include <fstream>          // Files
#include <boost/asio.hpp>   // Networking
#include <array>
#include <vector>
#include <string>
#include "dis_decoder.hpp"      
#include "enumeration_mapper.hpp"
#include "input_chacks.hpp"

using boost::asio::ip::udp;
using boost::asio::ip::address;

//#define IPADDRESS "192.168.0.255"
#define PACKET_SIZE 1280

int main()
{
    // Create IO Context (to talk to OS)
    boost::asio::io_context io_context;

    // Open Config File
    std::ifstream config_file;
    config_file.open ("config.txt");
    
    std::string line;   // Variable to hold file stream

    if (!config_file.is_open())
    {
        std::cerr << "Could not find config.txt" << std::endl;
        int i;
        std::cin >> i;

    }
    
    // Listening Port
    int listening_port = 0;
    std::getline(config_file, line);
    listening_port = std::stoi(line);
    std::cout << "Listening Port: " << listening_port << "\n";
    udp::endpoint endpoint(udp::v4(), listening_port);
    udp::socket input_socket(io_context, endpoint);

    // Sending Port
    int port_count;
    int send_port;
    std::vector<udp::endpoint> remote_endpoints;
    std::vector<std::string> ip_addresses;
    std::string ip_address;
    
    // Variable to hold enumeration changes
    std::vector<enumeration_map> enumeration_mappings;
    std::vector<enumeration_map> flag_mappings;

    // Set up mappings
    std::getline(config_file, line);
    port_count = std::stoi(line);
    std::cout << "Send port count: " << port_count << "\n";

    boost::asio::io_service io_service;
    udp::socket output_socket(io_service);
    
    for (int i = 0; i < port_count; i++)
    {
        int change_enum;
        int enum_name;
        int enum_flag_name;
        int enum_flag_val;

        if (port_count > 1)
            std::cout << "\n---PORT " << i + 1 << "---\n";
        // Get Send Port
        std::getline(config_file, line);
        send_port = std::stoi(line);
        if (send_port < 1024)
            std::cout << "Warning: Port " << send_port << " technically reserved!\nProgram will still run\n";
        std::cout << "Send Port: " << send_port << "\n";
        
        // Get send Ip address
        std::getline(config_file, line);
        ip_address = line;
        if (!is_valid_ip(line.data()))
        {
            int err;
            std::cerr << "Invalid IP Address for port " << send_port << "\n";
            std::cin >> err;
            return -1;
        }
            
        std::cout << "IP Address: " << ip_address << "\n";

        // Check if enumerations should be changed
        std::getline(config_file, line);
        change_enum = std::stoi(line);
        std::cout << "Enumerations Changed: " << change_enum << "\n";
        
        // Map enumeration changes if any
        if (change_enum >= 1)
        {
            enumeration_map flag_map;
            enumeration_map enumerations;

            for (int count = 0; count < change_enum; count++)
            {
                int flag_check_count;
                std::getline(config_file, line);
                flag_check_count = std::stoi(line);
                for (int i = 0; i < flag_check_count; i++)
                {
                    // Flag enum to check
                    std::getline(config_file, line);
                    enum_flag_name = std::stoi(line);
                    if (flag_map.return_string(enum_flag_name) == "Invalid Enumeration!")
                    {
                        std::cerr << "Invalid Enumeration!";
                        int i;
                        std::cin >> i;
                    }
                    std::cout << "Enumeration flag: " << flag_map.return_string(enum_flag_name) << "\n";

                    // Flag value to check
                    std::getline(config_file, line);
                    enum_flag_val = std::stoi(line);
                    std::cout << "Enumeration flag val: " << enum_flag_val << "\n";
                    
                    flag_map.add_flag(enum_flag_name, enum_flag_val);
                    flag_mappings.push_back(flag_map);
                }

                // Enumeration to be changed
                std::getline(config_file, line);
                enum_name = std::stoi(line);
                if (enumerations.return_string(enum_name) == "Invalid Enumeration!")
                {
                    std::cerr << "Invalid Enumeration!";
                    int i;
                    std::cin >> i;
                }
                std::cout << "Enumeration being changed: " << enumerations.return_string(enum_name) << "\n";
                enumerations.add_name(enum_name);

                // Value to change to
                std::getline(config_file, line);
                enum_name = std::stoi(line);
                std::cout << "Value to change to: " << line << "\n";
                enumerations.add_value(line);
            }
            enumeration_mappings.push_back(enumerations);
        }
        else
        {
            std::string enum_val;
            enumeration_map enumerations;

            std::cout << "False\n";
            enum_name = 0;
            enumerations.add_name(enum_name);

            enum_val = '0';
            enumerations.add_value(enum_val);

            enumeration_mappings.push_back(enumerations);
        }
        
        udp::endpoint remote_endpoint = udp::endpoint(address::from_string(ip_address), send_port);
        
        remote_endpoints.push_back(remote_endpoint);
        ip_addresses.push_back(ip_address);
    }  

    // Open socket
    output_socket.open(udp::v4());
    boost::system::error_code err;

    // Create a buffer
    std::array<unsigned char, PACKET_SIZE> recv_buf{};
    std::vector<unsigned char> send_buf;

    // Logic loop
    while (true)
    {
        // Create PDU variable
        pdu packet;
        std::array<unsigned char, sizeof(double)> packet_temp;  // variable to temporarily hold original packet values
        std::vector< std::array<unsigned char, sizeof(double)>> original_values; // variable to hold original packet values

        // Get buffer from OS
        input_socket.receive_from(
            boost::asio::buffer(recv_buf), endpoint);
        
        // Store buffer into PDU
        packet.get_packet(recv_buf);        
        
        // If PDU received send it to mappings
        if (packet.PDU_Length > 0)
        {
            for (size_t i = 0; i < remote_endpoints.size(); i++)
            {
                // Manipulate PDU if mapped
                if (enumeration_mappings[i].enumeration_name[0] != 0 && flag_mappings[i].check_flag(packet))
                {
                    for (size_t count = 0; count < enumeration_mappings[i].enumeration_name.size(); count++)
                    {
                        packet_temp = enumeration_mappings[i].edit_pdu(count, packet);
                        original_values.push_back(packet_temp);
                    }
                }

                // Create buffer to send
                send_buf = packet.return_packet();

                // Return PDU to previous state if changed
                if (original_values.size() > 0)
                {
                    for (size_t count = 0; count < original_values.size(); count++)
                    {
                        enumeration_mappings[i].edit_pdu(count, packet, original_values[count]);
                    }
                }

                // Send buffer
                output_socket.send_to(boost::asio::buffer(send_buf), remote_endpoints[i], 0, err);

                packet_temp = { 0 };
                original_values.clear();
                send_buf.clear();
            }
        }
    }

    // Close sending socket
    output_socket.close();
    
    return 0;
}