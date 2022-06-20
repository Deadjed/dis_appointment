#pragma once

#define PACKET_SIZE 1280

class pdu
{
public:
	// HEADER (96 bit stream, STORED AMOUNT HERE)
	uint16_t Protocol_Version;		// 8 
	uint16_t Exercise_Identifier;	// 8 
	uint16_t PDU_Type;				// 8
	std::string PDU_Type_name;
	uint16_t Protocol_Family;		// Comes in at 8 bits, Enumeration below
	std::string Protocol_Family_name;
	uint32_t Time_Stamp;			// 32
	uint16_t PDU_Length;			// 16
	uint16_t Padding;				// 16

	// ENTITY ID (48 bit strea, STORED AMOUNT HERE)
	//	Simulation Address Record	// 32
	uint16_t Site_Identifier;		// 16
	uint16_t Application_Identifier;// 16

	uint16_t Entity_Identity;		// 16

	// FORCE ID 8
	uint16_t Force_ID;				// 8
	std::string Force_ID_name;

	//# of Articulation Parameters (n) Field 8
	uint16_t no_Articulation_Parameters;	// 8

	// Entity Type 64
	uint16_t Kind;			// 8
	uint16_t Domain;		// 8
	uint16_t Country;		// 16
	uint16_t Category;		// 8
	uint16_t Subcategory;	// 8
	uint16_t Specific;		// 8
	uint16_t Extra;			// 8

	// Alternative Entity Type	64
	uint16_t Kind_alt;			// 8
	uint16_t Domain_alt;		// 8
	uint16_t Country_alt;		// 16
	uint16_t Category_alt;		// 8
	uint16_t Subcategory_alt;	// 8
	uint16_t Specific_alt;		// 8
	uint16_t Extra_alt;			// 8
	
	// Entity Linear Velocity	96
	float LV_First_Vector_Component;	// 32
	float LV_Second_Vector_Component;	// 32
	float LV_Third_Vector_Component;	// 32
	
	// Entity Location	192
	double Entity_x;	// 64
	double Entity_y;	// 64
	double Entity_z;	// 64
	
	// Entity Orientation	96
	float PSI;		// 32
	float THETA;	// 32
	float PHI;		// 32
	
	// Entity Appearance	32
	uint16_t General_Appearance;	// 16
	// Specific Appearance Variant	128
	uint16_t Appearance_Variant;
									
	// Dead Reckoning Parameters	320
	uint16_t Dead_Reckoning_Algorithm;	// 8 ENUMERATION
	// PAD type? Dead Reckoning Other Parameters 120 bits
	// Linear Acceleration	96
	float LA_First_Vector;	// 32
	float LA_Second_Vector;	// 32
	float LA_Third_Vector;	// 32
	// Entity Angular Velocity	96
	float Rate_About_X;		// 32
	float Rate_About_Y;		// 32
	float Rate_About_Z;		// 32

	// Entity Marking	96 (122)
	uint16_t Entity_Marking_Character_Set;	// 8 ENUMERATION
	// 88 bits (11 Bytes) String represented as unsigned int chars
	std::string Marking;	// 88
	
	// Entity Capabilities 32
	uint8_t Entity_Capabilities;
	
	// Articulation Parameter	128
	bool Parameter_Type_Designator;			// 8
	bool Parameter_Change_Indicator;		// 8
	uint16_t Articulation_Attachment_ID;	// 16
	// Parameter Type Varient	64
	uint32_t Attached_Parts;				// 32 ENUMERATION
	// Articulated Parts Record	32
	uint16_t Articulated_Parts_Low;			// 16 BITFIELD
	uint16_t Articulated_Parts_High;		// 16 BITFIELD
	double Articulation_Parameter_Value;	// 64

	/*
	 * Prints all of the DIS PDU information
	 */
	void print_packet();

	void print_header();
	void print_entity_identity();
	void print_entity_type();
	void print_alt_entity_type();
	void print_linear_velocity();
	void print_entity_location();
	void print_entity_orientation();
	void print_entity_appearance();
	void print_dead_reckoning();
	void print_marking();
	void print_entity_capabilities();
	void print_articulation_parameters();

	void get_packet(std::array<unsigned char, PACKET_SIZE>& buffer);

	std::vector<unsigned char> return_packet();
private:
	void get_header(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_entity_type(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_entity_type(std::array<unsigned char, PACKET_SIZE>& buffer);
	// HEADER 96
	void get_protocol_version(std::array<unsigned char, PACKET_SIZE> &buffer);
	void get_exercise_identifier(std::array<unsigned char, PACKET_SIZE> &buffer);
	void get_pdu_type(std::array<unsigned char, PACKET_SIZE> &buffer);				// Enumeration
	void get_protocol_family(std::array<unsigned char, PACKET_SIZE> &buffer);		// Enumeration
	void get_time_stamp(std::array<unsigned char, PACKET_SIZE> &buffer);
	void get_pdu_length(std::array<unsigned char, PACKET_SIZE> &buffer);
	void get_padding(std::array<unsigned char, PACKET_SIZE> &buffer);
	// ENTITY ID 48
	void get_site_identifier(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_application_identifier(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_entity_identity(std::array<unsigned char, PACKET_SIZE>& buffer);
	// FORCE ID 8
	void get_force_id(std::array<unsigned char, PACKET_SIZE>& buffer);
	//# of Articulation Parameters (n) Field 8
	void get_no_articulation_parameters(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Type Record 64
	void get_kind(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_domain(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_country(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_category(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_subcategory(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_specific(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_extra(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Alternate Entity Type Record 64
	void get_alt_kind(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_domain(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_country(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_category(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_subcategory(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_specific(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_alt_extra(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Linear Velocity Record	96
	void get_linear_velocity(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Location	192
	void get_entity_location(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Orientation 96
	void get_entity_orientation(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Appearance	32
	void get_entity_appearance(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_appearance_variant(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Dead Reckoning Parameters	320
	void get_dead_reckoning_algorithm(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_linear_acceleration(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_angular_velocity(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Marking	96
	void get_Entity_Marking_Character_Set(std::array<unsigned char, PACKET_SIZE>& buffer);
	void get_marking(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Entity Capabilities 32
	void get_entity_capabilities(std::array<unsigned char, PACKET_SIZE>& buffer);
	// Articulation Parameter	128
	void get_articulation_parameters(std::array<unsigned char, PACKET_SIZE>& buffer);
};