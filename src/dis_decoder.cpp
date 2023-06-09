#ifndef DIS_DECODER_H
#define DIS_DECODER_H

#include <iostream>
#include <array>
#include <vector>
#include <bit>				// bit_cast
#include <bitset>			// Printing bits
#include <string>
#include <cstring>			// 
#include <cstddef>			// memcpy
#include "dis_decoder.hpp"

#define PACKET_SIZE 1280

void pdu::print_packet()
{
	print_header();
	print_entity_identity();
	std::cout << "\nForce ID: \t\t" << Force_ID_name << "\n";
	std::cout << "\nArticulation Parameters: " << no_Articulation_Parameters << "\n";
	print_entity_type();
	print_alt_entity_type();
	print_linear_velocity();
	print_entity_location();
	print_entity_orientation();
	print_entity_appearance();
	print_dead_reckoning();
	print_marking();
	print_entity_capabilities();
	print_articulation_parameters();

}

void pdu::get_packet(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	get_header(buffer);
	get_site_identifier(buffer);
	get_application_identifier(buffer);
	get_entity_identity(buffer);
	get_force_id(buffer);
	get_no_articulation_parameters(buffer);
	get_entity_type(buffer);
	get_alt_entity_type(buffer);
	get_linear_velocity(buffer);
	get_entity_location(buffer);
	get_entity_orientation(buffer);
	get_entity_appearance(buffer);
	get_appearance_variant(buffer);
	get_dead_reckoning_algorithm(buffer);
	get_linear_acceleration(buffer);
	get_angular_velocity(buffer);
	get_Entity_Marking_Character_Set(buffer);
	get_marking(buffer);
	get_entity_capabilities(buffer);
	get_articulation_parameters(buffer);
}

std::vector<unsigned char> &pdu::return_packet()
{
	std::vector<unsigned char> packet;
	std::array<unsigned char, sizeof(double)> buf;

	// HEADER (96 bit stream, STORED AMOUNT HERE)
	packet.push_back(Protocol_Version & 0xff);		// 8 
	packet.push_back(Exercise_Identifier & 0xff);	// 8 
	packet.push_back(PDU_Type & 0xff);				// 8
	packet.push_back(Protocol_Family & 0xff);		// 8
	packet.push_back(Time_Stamp >> 24);
	packet.push_back(Time_Stamp >> 16);
	packet.push_back(Time_Stamp >> 8);
	packet.push_back(Time_Stamp & 0xff);			// 32
	packet.push_back(PDU_Length >> 8);
	packet.push_back(PDU_Length);			// 16
	packet.push_back(Padding >> 8);
	packet.push_back(Padding);				// 16

	// ENTITY ID (48 bit strea, STORED AMOUNT HERE)
	//	Simulation Address Record	// 32
	packet.push_back(Site_Identifier >> 8);
	packet.push_back(Site_Identifier);		// 16
	packet.push_back(Application_Identifier >> 8);
	packet.push_back(Application_Identifier);// 16


	packet.push_back(Entity_Identity >> 8);
	packet.push_back(Entity_Identity);		// 16

	// FORCE ID 8
	packet.push_back(Force_ID & 0xff);				// 8

	//# of Articulation Parameters (n) Field 8
	packet.push_back(no_Articulation_Parameters & 0xff);	// 8

	// Entity Type 64
	packet.push_back(Kind & 0xff);			// 8
	packet.push_back(Domain & 0xff);		// 8
	packet.push_back(Country >> 8);
	packet.push_back(Country);				// 16
	packet.push_back(Category & 0xff);		// 8
	packet.push_back(Subcategory & 0xff);	// 8
	packet.push_back(Specific & 0xff);		// 8
	packet.push_back(Extra & 0xff);			// 8

	// Alternative Entity Type	64
	packet.push_back(Kind_alt & 0xff);			// 8
	packet.push_back(Domain_alt & 0xff);		// 8
	packet.push_back(Country_alt >> 8);
	packet.push_back(Country_alt);				// 16
	packet.push_back(Category_alt & 0xff);		// 8
	packet.push_back(Subcategory_alt & 0xff);	// 8
	packet.push_back(Specific_alt & 0xff);		// 8
	packet.push_back(Extra_alt & 0xff);			// 8

	// Entity Linear Velocity	96
	std::memcpy(&buf, &LV_First_Vector_Component, sizeof(float));
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &LV_Second_Vector_Component, sizeof(float));
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &LV_Third_Vector_Component, sizeof(float));
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);

	// Entity Location	192
	std::memcpy(&buf, &Entity_x, sizeof(double));				// 64
	packet.push_back(buf[7]);	
	packet.push_back(buf[6]);
	packet.push_back(buf[5]);
	packet.push_back(buf[4]);
	packet.push_back(buf[3]);
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &Entity_y, sizeof(double));				// 64
	packet.push_back(buf[7]);
	packet.push_back(buf[6]);
	packet.push_back(buf[5]);
	packet.push_back(buf[4]);
	packet.push_back(buf[3]);
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &Entity_z, sizeof(double));				// 64
	packet.push_back(buf[7]);
	packet.push_back(buf[6]);
	packet.push_back(buf[5]);
	packet.push_back(buf[4]);
	packet.push_back(buf[3]);
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);

	// Entity Orientation	96
	std::memcpy(&buf, &PSI, sizeof(float));		// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &THETA, sizeof(float));				// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &PHI, sizeof(float));					// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);

	// Entity Appearance	32
	packet.push_back(General_Appearance >> 8);
	packet.push_back(General_Appearance);	// 16
	// Specific Appearance Variant	128
	packet.push_back(Appearance_Variant >> 8);
	packet.push_back(Appearance_Variant);	// 16

	// Dead Reckoning Parameters	320
	packet.push_back(Dead_Reckoning_Algorithm & 0xff);	// 8 ENUMERATION
	// PAD type? Dead Reckoning Other Parameters 120 bits
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	packet.push_back(0x00);
	// Linear Acceleration	96
	std::memcpy(&buf, &LA_First_Vector, sizeof(float));	// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &LA_Second_Vector, sizeof(float));	// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &LA_Third_Vector, sizeof(float));	// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	// Entity Angular Velocity	96
	std::memcpy(&buf, &Rate_About_X, sizeof(float));		// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &Rate_About_Y, sizeof(float));		// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	std::memcpy(&buf, &Rate_About_Z, sizeof(float));		// 32
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);

	// Entity Marking	96 (122)
	packet.push_back(Entity_Marking_Character_Set & 0xff);	// 8 ENUMERATION
	// 88 bits (11 Bytes) String represented as unsigned int chars
	packet.push_back(Marking[0]);	// 88
	packet.push_back(Marking[1]);
	packet.push_back(Marking[2]);
	packet.push_back(Marking[3]);
	packet.push_back(Marking[4]);
	packet.push_back(Marking[5]);
	packet.push_back(Marking[6]);
	packet.push_back(Marking[7]);
	packet.push_back(Marking[8]);
	packet.push_back(Marking[9]);
	packet.push_back(Marking[10]);

	// Entity Capabilities 32
	packet.push_back(Entity_Capabilities);
	packet.push_back(0x00);		// padding
	packet.push_back(0x00);
	packet.push_back(0x00);

	// Articulation Parameter	128
	packet.push_back(Parameter_Type_Designator);	// 8
	packet.push_back(Parameter_Change_Indicator);	// 8
	packet.push_back(Articulation_Attachment_ID >> 8);
	packet.push_back(Articulation_Attachment_ID);	// 16
	// Parameter Type Varient	64
	std::memcpy(&buf, &Attached_Parts, sizeof(float));				// 32 ENUMERATION
	packet.push_back(buf[3]);	// 32
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);
	// Articulated Parts Record	32
	packet.push_back(Articulated_Parts_Low >> 8);
	packet.push_back(Articulated_Parts_Low);			// 16 BITFIELD
	packet.push_back(Articulated_Parts_High >> 8);
	packet.push_back(Articulated_Parts_High);		// 16 BITFIELD
	std::memcpy(&buf, &Articulation_Parameter_Value, sizeof(double));	// 64
	packet.push_back(buf[7]);
	packet.push_back(buf[6]);
	packet.push_back(buf[5]);
	packet.push_back(buf[4]);
	packet.push_back(buf[3]);
	packet.push_back(buf[2]);
	packet.push_back(buf[1]);
	packet.push_back(buf[0]);

	// Change packet size field
	uint16_t size = packet.size();
	std::memcpy(&packet[8], &size, sizeof(uint16_t));

	return packet;
}

//-------------
//   HEADER
//-------------
// 96 bits
void pdu::print_header()
{
	std::cout << "\n\n------------------------\n     Header\n------------------------\n"
		<< "\nProtocol Version: \t" << Protocol_Version
		<< "\nExercise Identifier: \t" << Exercise_Identifier
		<< "\nPDU Type: \t\t" << PDU_Type_name
		<< "\nProtocol Family: \t" << Protocol_Family_name
		<< "\nTime Stamp: \t\t" << Time_Stamp
		<< "\nPDU Length: \t\t" << PDU_Length
		<< "\nPadding: \t\t" << Padding
		<< std::endl;

}

void pdu::get_header(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	get_protocol_version(buffer);
	get_exercise_identifier(buffer);
	get_pdu_type(buffer);
	get_protocol_family(buffer);
	get_time_stamp(buffer);
	get_pdu_length(buffer);
	get_padding(buffer);
}

void pdu::get_protocol_version(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	Protocol_Version = uint16_t(buffer[0]);
}

void pdu::get_exercise_identifier(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	Exercise_Identifier = uint16_t(buffer[1]);
}

void pdu::get_pdu_type(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	PDU_Type = uint16_t(buffer[2]);
	switch (PDU_Type)
	{
	case 1:
		PDU_Type_name = "Entity State";
		break;
	case 2:
		PDU_Type_name = "Fire";
		break;
	case 3:
		PDU_Type_name = "Detonation";
		break;
	case 4:
		PDU_Type_name = "Collision";
		break;
	case 5:
		PDU_Type_name = "Service Request";
		break;
	case 6:
		PDU_Type_name = "Resupply Offer";
		break;
	case 7:
		PDU_Type_name = "Resupply Received";
		break;
	case 8:
		PDU_Type_name = "Resupply Cancel";
		break;
	case 9:
		PDU_Type_name = "Repair Complete";
		break;
	case 10:
		PDU_Type_name = "Repair Response";
		break;
	case 11:
		PDU_Type_name = "Create Entity";
		break;
	case 12:
		PDU_Type_name = "Remove Entity";
		break;
	case 13:
		PDU_Type_name = "Start / Resume";
		break;
	case 14:
		PDU_Type_name = "Stop / Freeze";
		break;
	case 15:
		PDU_Type_name = "Acknowledge";
		break;
	case 16:
		PDU_Type_name = "Action Request";
		break;
	case 17:
		PDU_Type_name = "Action Response";
		break;
	case 18:
		PDU_Type_name = "Data Query";
		break;
	case 19:
		PDU_Type_name = "Set Data";
		break;
	case 20:
		PDU_Type_name = "Data";
		break;
	case 21:
		PDU_Type_name = "Event Report";
		break;
	case 22:
		PDU_Type_name = "Comment";
		break;
	case 23:
		PDU_Type_name = "Electromagnetic Emission";
		break;
	case 24:
		PDU_Type_name = "Designator";
		break;
	case 25:
		PDU_Type_name = "Transmitter";
		break;
	case 26:
		PDU_Type_name = "Signal";
		break;
	case 27:
		PDU_Type_name = "Receiver";
		break;
	case 129:
		PDU_Type_name = "Announce Object";
		break;
	case 130:
		PDU_Type_name = "Delete Object";
		break;
	case 131:
		PDU_Type_name = "Describe Application";
		break;
	case 132:
		PDU_Type_name = "Describe Event";
		break;
	case 133:
		PDU_Type_name = "Describe Object";
		break;
	case 134:
		PDU_Type_name = "Request Event";
		break;
	case 135:
		PDU_Type_name = "Request Object";
		break;
	case 140:
		PDU_Type_name = "Time Space Position Indicator - FI";
		break;
	case 141:
		PDU_Type_name = "Appearance - FI";
		break;
	case 142:
		PDU_Type_name = "Articulated Parts - FI";
		break;
	case 143:
		PDU_Type_name = "Fire - FI";
		break;
	case 144:
		PDU_Type_name = "Detonation - FI";
		break;
	case 150:
		PDU_Type_name = "Point Object State";
		break;
	case 151:
		PDU_Type_name = "Linear Object State";
		break;
	case 152:
		PDU_Type_name = "Areal Object State";
		break;
	case 153:
		PDU_Type_name = "Environment";
		break;
	case 155:
		PDU_Type_name = "Transfer Control Request";
		break;
	case 156:
		PDU_Type_name = "Transfer Control";
		break;
	case 157:
		PDU_Type_name = "Transfer Control Acknowledge";
		break;
	case 160:
		PDU_Type_name = "Intercom Control";
		break;
	case 161:
		PDU_Type_name = "Intercom Signal";
		break;
	case 170:
		PDU_Type_name = "Aggregate";
		break;
	default:
		PDU_Type_name = "Other";
	}

}

void pdu::get_protocol_family(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	Protocol_Family = uint16_t(buffer[3]);
	
	switch (Protocol_Family)
	{
	case 1:
		Protocol_Family_name = "Entity Information / Interaction";
		break;
	case 2:
		Protocol_Family_name = "Warfare";
		break;
	case 3:
		Protocol_Family_name = "Logistics";
		break;
	case 4:
		Protocol_Family_name = "Radio Communication";
		break;
	case 5:
		Protocol_Family_name = "Simulation Management";
		break;
	case 6:
		Protocol_Family_name = "Distributed Emission Regeneration";
		break;
	case 129:
		Protocol_Family_name = "Experimental - CGF";
		break;
	case 130:
		Protocol_Family_name = "Experimental - Entity Interaction / Information - Field Instrumentation";
		break;
	case 131:
		Protocol_Family_name = "Experimental - Warfare Field Instrumentation";
		break;
	case 132:
		Protocol_Family_name = "Experimental - Environment Object Information / Interaction";
		break;
	case 133:
		Protocol_Family_name = "Experimental - Entity Management";
		break;
	default:
		Protocol_Family_name = "other";
	}
		
}

void pdu::get_time_stamp(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	Time_Stamp = (buffer[4] << (8 * 3) | buffer[5] << (8 * 2) | buffer[6] << 8 << buffer[7]);
}

void pdu::get_pdu_length(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	PDU_Length = (buffer[8] << 8) | buffer[9];
}

void pdu::get_padding(std::array<unsigned char, PACKET_SIZE> &buffer)
{
	Padding = (buffer[10] << 8) | buffer[11];
}

//-----------------------
//   ENTITY IDENTITY
//-----------------------
// 48 bits
void pdu::print_entity_identity()
{
	std::cout << "\n------------------------\n     Entity Identity\n------------------------\n"
		<< "\nSite Identifier: \t" << Site_Identifier
		<< "\nApplication Identifier: " << Application_Identifier
		<< "\nEntity Identity: \t" << Entity_Identity
		<< std::endl;
}

void pdu::get_site_identifier(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Site_Identifier = (buffer[12] << 8) | buffer[13];
}

void pdu::get_application_identifier(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Application_Identifier = (buffer[14] << 8) | buffer[15];
}

void pdu::get_entity_identity(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Entity_Identity = (buffer[16] << 8) | buffer[17];
}

//-----------------------
//   FORCE ID
//-----------------------
// 8 bits
void pdu::get_force_id(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Force_ID = uint16_t(buffer[18]);

	switch (Force_ID)
	{
	case 1:
		Force_ID_name = "Friendly";
		break;
	case 2:
		Force_ID_name = "Opposing";
		break;
	case 3:
		Force_ID_name = "Neutral";
		break;
	default:
		Force_ID_name = "Other";
	}		
}

//-----------------------
//   # of Articulation Parameters (n) Field
//-----------------------
// 8 bits
void pdu::get_no_articulation_parameters(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	no_Articulation_Parameters = uint16_t(buffer[19]);
}

//-----------------------
//   ENTITY TYPE
//-----------------------
// 64 bits
void pdu::print_entity_type()
{
	std::cout << "\n\n------------------------\n     ENTITY TYPE\n------------------------\n"
		<< "\nKind: \t\t" << Kind
		<< "\nDomain: \t" << Domain
		<< "\nCountry: \t" << Country
		<< "\nCategory: \t" << Category
		<< "\nSubcategory: \t" << Subcategory
		<< "\nSpecific: \t" << Specific
		<< "\nExtra: \t\t" << Extra
		<< std::endl;

}

void pdu::get_entity_type(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	get_kind(buffer);
	get_domain(buffer);
	get_country(buffer);
	get_category(buffer);
	get_subcategory(buffer);
	get_specific(buffer);
	get_extra(buffer);

}

void pdu::get_kind(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Kind = uint16_t(buffer[20]);
	// ADD ENUMERATIONS
	//0	Other
	//1	Platform
	//2	Munition
	//3	Life form
	//4	Environmental
	//5	Cultural feature
	//6	Supply
	//7	Radio
	//8	Expendable
	//9	Sensor / Emitter
}

void pdu::get_domain(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Domain = uint16_t(buffer[21]);
	/*
	0 Other
	1 Land
	2 Air
	3 Surface
	4 Subsurface
	5 Space
	*/
}

void pdu::get_country(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Country = uint16_t(buffer[22] << 8 | buffer[23]);
}

void pdu::get_category(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Category = uint16_t(buffer[24]);
}

void pdu::get_subcategory(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Subcategory = uint16_t(buffer[25]);
}

void pdu::get_specific(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Specific = uint16_t(buffer[26]);
}

void pdu::get_extra(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Extra = uint16_t(buffer[27]);
}

//-----------------------
//   ALTERNATE ENTITY TYPE
//-----------------------
// 64 bits
void pdu::print_alt_entity_type()
{
	std::cout << "\n\n------------------------\n     Alternate Entity Type\n------------------------\n"
		<< "\nKind: \t\t" << Kind_alt
		<< "\nDomain: \t" << Domain_alt
		<< "\nCountry: \t" << Country_alt
		<< "\nCategory: \t" << Category_alt
		<< "\nSubcategory: \t" << Subcategory_alt
		<< "\nSpecific: \t" << Specific_alt
		<< "\nExtra: \t\t" << Extra_alt
		<< std::endl;

}

void pdu::get_alt_entity_type(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	get_alt_kind(buffer);
	get_alt_domain(buffer);
	get_alt_country(buffer);
	get_alt_category(buffer);
	get_alt_subcategory(buffer);
	get_alt_specific(buffer);
	get_alt_extra(buffer);

}

void pdu::get_alt_kind(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Kind_alt = uint16_t(buffer[28]);
	// ADD ENUMERATIONS
	//0	Other
	//1	Platform
	//2	Munition
	//3	Life form
	//4	Environmental
	//5	Cultural feature
	//6	Supply
	//7	Radio
	//8	Expendable
	//9	Sensor / Emitter
}

void pdu::get_alt_domain(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Domain_alt = uint16_t(buffer[29]);
}

void pdu::get_alt_country(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Country_alt = uint16_t(buffer[30] << 8 | buffer[31]);
}

void pdu::get_alt_category(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Category_alt = uint16_t(buffer[32]);
}

void pdu::get_alt_subcategory(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Subcategory_alt = uint16_t(buffer[33]);
}

void pdu::get_alt_specific(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Specific_alt = uint16_t(buffer[34]);
}

void pdu::get_alt_extra(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Extra_alt = uint16_t(buffer[35]);
}

//-----------------------
//   Entity Linear Velocity	
//-----------------------
// 96 bits
void pdu::print_linear_velocity()
{
	std::cout << "\n\n------------------------\n     Linear Velocity\n------------------------\n"
		<< "\nFirst Component: \t" << LV_First_Vector_Component
		<< "\nSecond Component: \t" << LV_Second_Vector_Component
		<< "\nThird Component: \t" << LV_Third_Vector_Component
		<< std::endl;
}

void pdu::get_linear_velocity(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	std::memcpy(&LV_First_Vector_Component, &buffer[36], sizeof(float));
	std::reverse((std::byte*)&LV_First_Vector_Component, (std::byte*)&LV_First_Vector_Component + sizeof(float));
	std::memcpy(&LV_Second_Vector_Component, &buffer[40], sizeof(float));
	std::reverse((std::byte*)&LV_Second_Vector_Component, (std::byte*)&LV_Second_Vector_Component + sizeof(float));
	std::memcpy(&LV_Third_Vector_Component, &buffer[44], sizeof(float));
	std::reverse((std::byte*)&LV_Third_Vector_Component, (std::byte*)&LV_Third_Vector_Component + sizeof(float));
}

//-----------------------
//   Entity Location	
//-----------------------
// 192 bits
void pdu::print_entity_location()
{
	std::cout << "\n\n------------------------\n     Entity Location\n------------------------\n"
		<< "\nX: \t\t" << Entity_x
		<< "\nY: \t\t" << Entity_y
		<< "\nZ: \t\t" << Entity_z
		<< std::endl;
}

void pdu::get_entity_location(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	std::memcpy(&Entity_x, &buffer[48], sizeof(double));
	std::reverse((std::byte*)&Entity_x, (std::byte*)&Entity_x + sizeof(double));
	std::memcpy(&Entity_y, &buffer[56], sizeof(double));
	std::reverse((std::byte*)&Entity_y, (std::byte*)&Entity_y + sizeof(double));
	std::memcpy(&Entity_z, &buffer[64], sizeof(double));
	std::reverse((std::byte*)&Entity_z, (std::byte*)&Entity_z + sizeof(double));
}

//-----------------------
//   Entity Orientation	
//-----------------------
// 96 bits
void pdu::print_entity_orientation()
{
	std::cout << "\n\n------------------------\n     Entity Orientation\n------------------------\n"
		<< "\PSI: \t\t" << PSI
		<< "\nTHETA: \t\t" << THETA
		<< "\nPHI: \t\t" << PHI
		<< std::endl;
}

void pdu::get_entity_orientation(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	std::memcpy(&PSI, &buffer[72], sizeof(float));
	std::reverse((std::byte*)&PSI, (std::byte*)&PSI + sizeof(float));
	std::memcpy(&THETA, &buffer[76], sizeof(float));
	std::reverse((std::byte*)&THETA, (std::byte*)&THETA + sizeof(float));
	std::memcpy(&PHI, &buffer[80], sizeof(float));
	std::reverse((std::byte*)&PHI, (std::byte*)&PHI + sizeof(float));
}

//-----------------------
//   Entity Appearance	
//-----------------------
// 96 bits
void pdu::print_entity_appearance()
{
	std::cout << "\n\n------------------------\n     Entity Appearance\n------------------------\n"
		<< "\nEntity Appearance: \t" << std::bitset<16>(General_Appearance)
		<< "\nAppearance Variant: \t" << std::bitset<16>(Appearance_Variant)
		<< std::endl;
}

void pdu::get_entity_appearance(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	General_Appearance = uint16_t(buffer[84] << 8 | buffer[85]);

}

void pdu::get_appearance_variant(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Appearance_Variant = uint16_t(buffer[86] << 8 | buffer[87]);
	/*
	if (Domain == 1)
		Land_Platforms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	else if (Domain == 2)
		Air_Platforms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	else if (Domain == 3)
		Surface_Platforms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	else if (Domain == 4)
		Subsurface_Platforms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	else if (Domain == 5)
		Space_Platforms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	// Guided_Munitions
	
	else if (Kind == 3)
		Life_Forms = uint16_t(buffer[86] << 8 | buffer[87]);
	
	else if (Kind == 4)
		Environmentals = uint16_t(buffer[86] << 8 | buffer[87]);
	*/
}

//-----------------------
//   Dead Reckoning	
//-----------------------
// 320 bits
void pdu::print_dead_reckoning()
{
	std::cout << "\n\n------------------------\n     Dead Reckoning\n------------------------\n"
		<< "\nAlgorithm: \t" << Dead_Reckoning_Algorithm
		<< "\nLinear Acceleration (first component): \t" << LA_First_Vector
		<< "\nLinear Acceleration (second component): " << LA_Second_Vector
		<< "\nLinear Acceleration (Third component): \t" << LA_Third_Vector
		<< "\nAngular Velocity X: \t" << Rate_About_X
		<< "\nAngular Velocity Y: \t" << Rate_About_Y
		<< "\nAngular Velocity Z: \t" << Rate_About_Z
		<< std::endl;
}

void pdu::get_dead_reckoning_algorithm(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Dead_Reckoning_Algorithm = uint16_t(buffer[88]);
}

// PAD type? Dead Reckoning Other Parameters 120 bits

void pdu::get_linear_acceleration(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	std::memcpy(&LA_First_Vector, &buffer[104], sizeof(float));
	std::reverse((std::byte*)&LA_First_Vector, (std::byte*)&LA_First_Vector + sizeof(float));
	std::memcpy(&LA_Second_Vector, &buffer[108], sizeof(float));
	std::reverse((std::byte*)&LA_Second_Vector, (std::byte*)&LA_Second_Vector + sizeof(float));
	std::memcpy(&LA_Third_Vector, &buffer[112], sizeof(float));
	std::reverse((std::byte*)&LA_Third_Vector, (std::byte*)&LA_Third_Vector + sizeof(float));
}

void pdu::get_angular_velocity(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	std::memcpy(&Rate_About_X, &buffer[116], sizeof(float));
	std::reverse((std::byte*)&Rate_About_X, (std::byte*)&Rate_About_X + sizeof(float));
	std::memcpy(&Rate_About_Y, &buffer[120], sizeof(float));
	std::reverse((std::byte*)&Rate_About_Y, (std::byte*)&Rate_About_Y + sizeof(float));
	std::memcpy(&Rate_About_Z, &buffer[124], sizeof(float));
	std::reverse((std::byte*)&Rate_About_Z, (std::byte*)&Rate_About_Z + sizeof(float));
}

//-----------------------
//   Marking	
//-----------------------
// 96 bits
void pdu::print_marking()
{
	std::cout << "\n\n------------------------\n     Marking\n------------------------\n"
		<< "\nMarking Char set: \t" << Entity_Marking_Character_Set
		<< "\nMarking: \t" << Marking
		<< std::endl;
}

void pdu::get_Entity_Marking_Character_Set(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Entity_Marking_Character_Set = uint16_t(buffer[128]);
}

void pdu::get_marking(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	for (size_t i = 0; i < 11; i++)
		Marking.push_back(buffer[i + 129]);
}

//-----------------------
//   Entity Capabilites	
//-----------------------
// 32 bits
void pdu::print_entity_capabilities()
{
	std::cout << "\n\n------------------------\n     Entity Capabilities\n------------------------\n"
		<< "\nAmunition Supply: \t" << std::bitset<8>(Entity_Capabilities)[4]
		<< "\nFuel Supply: \t\t" << std::bitset<8>(Entity_Capabilities)[5]
		<< "\nRecovery: \t\t" << std::bitset<8>(Entity_Capabilities)[6]
		<< "\nRepair: \t\t" << std::bitset<8>(Entity_Capabilities)[7]
		<< std::endl;
	/*
		Amunition Supply Field	1
		Fuel Supply Field	1
		Recovery Field	1
		Repair Field	1
		Unused Field	28
	*/
}

void pdu::get_entity_capabilities(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	Entity_Capabilities = uint8_t(buffer[140]);
}

//-----------------------
//   Articulation Parameter	
//-----------------------
// 32 bits
void pdu::print_articulation_parameters()
{
	std::cout << "\n\n------------------------\n     Articulation Parameters\n------------------------\n"
		<< "\nParameter Type: \t\t" << std::bitset<8>(Parameter_Type_Designator)
		<< "\nParameter Change: \t\t" << std::bitset<8>(Parameter_Change_Indicator)
		<< "\nArticulation Attachment: \t" << Articulation_Attachment_ID
		<< "\nAttached Parts: \t\t" << Attached_Parts
		<< "\nArticulated Parts Low: \t\t" << std::bitset<16>(Articulated_Parts_Low)
		<< "\nArticulated Parts High: \t" << std::bitset<16>(Articulated_Parts_High)
		<< "\nArticulation Parameter Value: \t" << Articulation_Parameter_Value
		<< std::endl;
}

void pdu::get_articulation_parameters(std::array<unsigned char, PACKET_SIZE>& buffer)
{
	// Articulation Parameter	128
	Parameter_Type_Designator = uint8_t(buffer[144]);			
	Parameter_Change_Indicator = uint8_t(buffer[145]);		
	Articulation_Attachment_ID = uint16_t(buffer[146] << 8 | buffer[147]);	
	// Parameter Type Varient	64
	Attached_Parts = uint32_t(buffer[148] << (8 * 3) | buffer[149] << (8 * 2) | buffer[150] << 8 | buffer[151]);
	// Articulated Parts Record	32
	Articulated_Parts_Low = uint16_t(buffer[152] << 8 | buffer[153]);
	Articulated_Parts_High = uint16_t(buffer[154] << 8 | buffer[155]);
	std::memcpy(&Articulation_Parameter_Value, &buffer[156], sizeof(double));
	std::reverse((std::byte*)&Articulation_Parameter_Value, (std::byte*)&Articulation_Parameter_Value + sizeof(double));
}


#endif // DIS_DECODER_H

