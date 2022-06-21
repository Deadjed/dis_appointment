#pragma once

#include "dis_decoder.hpp"

enum enumerators
{
    No_change,
    Protocol_Version,		// 8 
    Exercise_Identifier,	// 8 
    PDU_Type,				// 8
    Protocol_Family,		// 8
    Time_Stamp,			    // 32
    PDU_Length,			    // 16
    Padding,				// 16
    Site_Identifier,		// 16
    Application_Identifier, // 16
    Entity_Identity,		// 16
    Force_ID,				// 8
    no_Articulation_Parameters,	// 8
    Kind,			// 8
    Domain,		    // 8
    Country,		// 16
    Category,		// 8
    Subcategory,	// 8
    Specific,		// 8
    Extra,			// 8
    Kind_alt,			// 8
    Domain_alt,		    // 8
    Country_alt,		// 16
    Category_alt,		// 8
    Subcategory_alt,	// 8
    Specific_alt,		// 8
    Extra_alt,			// 8
    LV_First_Vector_Component,	// 32
    LV_Second_Vector_Component,	// 32
    LV_Third_Vector_Component,	// 32
    Entity_x,	// 64
    Entity_y,	// 64
    Entity_z,	// 64
    PSI,		// 32
    THETA,	    // 32
    PHI,		// 32
    General_Appearance,	        // 16
    Appearance_Variant,         // 16
    Dead_Reckoning_Algorithm,	// 8 ENUMERATION
    LA_First_Vector,	// 32
    LA_Second_Vector,	// 32
    LA_Third_Vector,	// 32
    Rate_About_X,		// 32
    Rate_About_Y,		// 32
    Rate_About_Z,		// 32
    Entity_Marking_Character_Set,	// 8 ENUMERATION
    Marking,	        // 88
    Entity_Capabilities,
    Parameter_Type_Designator,		// 8
    Parameter_Change_Indicator,		// 8
    Articulation_Attachment_ID,	    // 16
    Attached_Parts,				    // 32 ENUMERATION
    Articulated_Parts_Low,			// 16 BITFIELD
    Articulated_Parts_High,		    // 16 BITFIELD
    Articulation_Parameter_Value	// 64
};

class enumeration_map
{
public:
    std::vector<std::array<int, 2>> enumeration_flag;
    std::vector<enumerators> enumeration_name;
    std::vector<std::array<unsigned char, sizeof(double)>> enumeration_value;

    void add_flag(int& flag_name, int& flag_val);
    void add_name(int& name);
    void add_value(std::string& value);

    bool check_flag(pdu& pdu);

    std::string return_string(int& index);

    std::array<unsigned char, sizeof(double)> &edit_pdu(size_t& location, pdu& pdu);
    void edit_pdu(size_t& location, pdu& pdu, std::array<unsigned char, sizeof(double)>& value);
};