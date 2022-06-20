#ifndef ENUMERATION_MAPPER_H
#define ENUMERATION_MAPPER_H

#include <array>
#include <vector>
#include <cstddef>	// memcpy
#include <string>
#include <bitset>

#include <algorithm>
#include <iostream>

#include "enumeration_mapper.hpp"
#include "dis_decoder.hpp"

void enumeration_map::add_flag(int& flag_name, int& flag_val)
{
    std::array<int, 2 > result{ flag_name, flag_val };
    enumeration_flag.push_back(result);
}

void enumeration_map::add_name(int& name)
{
	enumerators result = static_cast<enumerators>(name);
	enumeration_name.push_back(result);
}

void enumeration_map::add_value(std::string& value)
{
    char char_stream[8];
	std::array<unsigned char, sizeof(double)> char_value;
    int i = 0;
    
    // Convert string to int
    i = std::stoi(value);
	
    std::memcpy(&char_value, &i, sizeof(i));
    
    //std::reverse((std::byte*)&char_value, (std::byte*)&char_value + sizeof(double));
	enumeration_value.push_back(char_value);
}

bool enumeration_map::check_flag(pdu& pdu)
{
    if (enumeration_flag.size() < 1)
        return false;
    for (auto &flag : enumeration_flag)
    {
        switch (flag[0])
        {
        case 1:
            if (flag[1] == pdu.Protocol_Version)
                break;		// 8 
            return false;
        case 2:
            if (flag[1] == pdu.Exercise_Identifier)
                break;	// 8 
            return false;
        case 3:
            if (flag[1] == pdu.PDU_Type)
                break;			// 8
            return false;
        case 4:
            if (flag[1] == pdu.Protocol_Family)
                break;	// 8
            return false;
        case 5:
            if (flag[1] == pdu.Time_Stamp)
                break;	    // 32
            return false;
        case 6:
            if (flag[1] == pdu.PDU_Length)
                break;		    // 16
            return false;
        case 7:
            if (flag[1] == pdu.Padding)
                break;			// 16
            return false;
        case 8:
            if (flag[1] == pdu.Site_Identifier)
                break;		// 16
            return false;
        case 9:
            if (flag[1] == pdu.Application_Identifier)
                break;// 16
            return false;
        case 10:
            if (uint16_t(flag[1]) == pdu.Entity_Identity)
                break;	// 16
            return false;
        case 11:
            if (flag[1] == pdu.Force_ID)
                break;		// 8
            return false;
        case 12:
            if (flag[1] == pdu.no_Articulation_Parameters)
                break;	// 8
            return false;
        case 13:
            if (flag[1] == pdu.Kind)
                break;		// 8
            return false;
        case 14:
            if (flag[1] == pdu.Domain)
                break;		    // 8
            return false;
        case 15:
            if (flag[1] == pdu.Country)
                break;		// 16
            return false;
        case 16:
            if (flag[1] == pdu.Category)
                break;	// 8
            return false;
        case 17: 
            if (flag[1] == pdu.Subcategory)
                break;// 8
            return false;
        case 18:
            if (flag[1] == pdu.Specific)
                break;		// 8
            return false;
        case 19:
            if (flag[1] == pdu.Extra)
                break;	// 8
            return false;
        case 20: 
            if (flag[1] == pdu.Kind_alt)
                break;		// 8
            return false;
        case 21: 
            if (flag[1] == pdu.Domain_alt)
                break;		    // 8
            return false;
        case 22: 
            if (flag[1] == pdu.Country_alt)
                break;	// 16
            return false;
        case 23: 
            if (flag[1] == pdu.Category_alt)
                break;	// 8
            return false;
        case 24:
            if (flag[1] == pdu.Subcategory_alt)
                break;	// 8
            return false;
        case 25: 
            if (flag[1] == pdu.Specific_alt)
                break;	// 8
            return false;
        case 26:
            if (flag[1] == pdu.Extra_alt)
                break;	// 8
            return false;
        case 27:
            if (flag[1] == pdu.LV_First_Vector_Component)
                break;	// 32
            return false;
        case 28:
            if (flag[1] == pdu.LV_Second_Vector_Component)
                break;	// 32
            return false;
        case 29:
            if (flag[1] == pdu.LV_Third_Vector_Component)
                break;// 32
            return false;
        case 30: 
            if (flag[1] == pdu.Entity_x)
                break;	// 64
            return false;
        case 31:
            if (flag[1] == pdu.Entity_y)
                break;
            return false;// 64
        case 32: 
            if (flag[1] == pdu.Entity_z)
                break;
            return false;   // 64
        case 33: 
            if (flag[1] == pdu.PSI)
                break;	// 32
            return false;
        case 34: 
            if (flag[1] == pdu.THETA)
                break;  // 32
            return false;
        case 35: 
            if (flag[1] == pdu.PHI)
                break;// 32;
            return false;
        case 36: 
            if (flag[1] == pdu.General_Appearance)
                break;	        // 16
            return false;
        case 37:
            if (flag[1] == pdu.Appearance_Variant)
                break;     // 16
            return false;
        case 38:
            if (flag[1] == pdu.Dead_Reckoning_Algorithm)
                break;	// 8 ENUMERATION
            return false;
        case 39: 
            //return "LA_First_Vector";// 32
            break;
        case 40: 
            //return "LA_Second_Vector";// 32
            break;
        case 41: 
            //return "LA_Third_Vector";// 32
            break;
        case 42: 
            //return "Rate_About_X";	// 32
            break;
        case 43: 
            //return "Rate_About_Y";	// 32
            break;
        case 44: 
            //return "Rate_About_Z";	// 32
            break;
        case 45:
            if (flag[1] == pdu.Entity_Marking_Character_Set)
                break;	// 8 ENUMERATION
            return false;
        case 46: 
            //if (flag[1] == pdu.Marking)
            break;        // 88
            return false;
        case 47: 
            if (flag[1] == pdu.Entity_Capabilities)
                break;
            return false;
        case 48:
            if (flag[1] == pdu.Parameter_Type_Designator)
                break;	// 8
            return false;
        case 49: 
            if (flag[1] == pdu.Parameter_Change_Indicator)
                break;		// 8
            return false;
        case 50:
            if (flag[1] == pdu.Articulation_Attachment_ID)
                break;	    // 16
            return false;
        case 51: 
            if (flag[1] == pdu.Attached_Parts)
                break;		    // 32 ENUMERATION
            return false;
        case 52: 
            if (flag[1] == pdu.Articulated_Parts_Low)
                break;		// 16 BITFIELD
            return false;
        case 53: 
            if (flag[1] == pdu.Articulated_Parts_High)
                break;		    // 16 BITFIELD
            return false;
        case 54: 
            if (flag[1] == pdu.Articulation_Parameter_Value)
                break;	// 64
            return false;
        //default: return false;
        }
    }

    return true;
}

std::string enumeration_map::return_string(int& index)
{
    switch (index)
    {
    case 0: return "No_change";
    case 1: return "Protocol_Version";		// 8 
    case 2: return "Exercise_Identifier";	// 8 
    case 3: return "PDU_Type";			// 8
    case 4: return "Protocol_Family";	// 8
    case 5: return "Time_Stamp";	    // 32
    case 6: return "PDU_Length";		    // 16
    case 7: return "Padding";			// 16
    case 8: return "Site_Identifier";		// 16
    case 9: return "Application_Identifier";// 16
    case 10: return "Entity_Identity";	// 16
    case 11: return "Force_ID";		// 8
    case 12: return "no_Articulation_Parameters";	// 8
    case 13: return "Kind";		// 8
    case 14: return "Domain";		    // 8
    case 15: return "Country";		// 16
    case 16: return "Category";	// 8
    case 17: return "Subcategory";// 8
    case 18: return "Specific";		// 8
    case 19: return "Extra";	// 8
    case 20: return "Kind_alt";		// 8
    case 21: return "Domain_alt";		    // 8
    case 22: return "Country_alt";	// 16
    case 23: return "Category_alt";	// 8
    case 24: return "Subcategory_alt";	// 8
    case 25: return "Specific_alt";	// 8
    case 26: return "Extra_alt";	// 8
    case 27: return "LV_First_Vector_Component";	// 32
    case 28: return "LV_Second_Vector_Component";	// 32
    case 29: return "LV_Third_Vector_Component";// 32
    case 30: return "Entity_x";	// 64
    case 31: return "Entity_y";// 64
    case 32: return "Entity_z";	// 64
    case 33: return "PSI";	// 32
    case 34: return "THETA";  // 32
    case 35: return "PHI";// 32;
    case 36: return "General_Appearance";	        // 16
    case 37: return "Appearance_Variant";     // 16
    case 38: return "Dead_Reckoning_Algorithm";	// 8 ENUMERATION
    case 39: return "LA_First_Vector";// 32
    case 40: return "LA_Second_Vector";// 32
    case 41: return "LA_Third_Vector";// 32
    case 42: return "Rate_About_X";	// 32
    case 43: return "Rate_About_Y";	// 32
    case 44: return "Rate_About_Z";	// 32
    case 45: return "Entity_Marking_Character_Set";	// 8 ENUMERATION
    case 46: return "Marking";        // 88
    case 47: return "Entity_Capabilities";
    case 48: return "Parameter_Type_Designator";	// 8
    case 49: return "Parameter_Change_Indicator";		// 8
    case 50: return "Articulation_Attachment_ID";	    // 16
    case 51: return "Attached_Parts";		    // 32 ENUMERATION
    case 52: return "Articulated_Parts_Low";		// 16 BITFIELD
    case 53: return "Articulated_Parts_High";		    // 16 BITFIELD
    case 54: return "Articulation_Parameter_Value";	// 64
    default: return "Invalid Enumeration!";
    }
}

std::array<unsigned char, sizeof(double)> enumeration_map::edit_pdu(size_t& location, pdu& pdu)
{
    std::array<unsigned char, sizeof(double)> temp{ '0' };

    if (enumeration_name.at(location) != 0)
    {
        switch (enumeration_name.at(location))
        {
        case 1:
            std::memcpy(&temp, &pdu.Protocol_Version, sizeof(pdu.Protocol_Version));
            std::memcpy(&pdu.Protocol_Version, &enumeration_value.at(location), sizeof(pdu.Protocol_Version));
            return temp;
        case 2:
            std::memcpy(&temp, &pdu.Exercise_Identifier, sizeof(pdu.Exercise_Identifier));
            std::memcpy(&pdu.Exercise_Identifier, &enumeration_value.at(location), sizeof(pdu.Exercise_Identifier));
            return temp;
        case 3:
            std::memcpy(&temp, &pdu.PDU_Type, sizeof(pdu.PDU_Type));
            std::memcpy(&pdu.PDU_Type, &enumeration_value.at(location), sizeof(pdu.PDU_Type));
            return temp;
        case 4:
            std::memcpy(&temp, &pdu.Protocol_Family, sizeof(pdu.Protocol_Family));
            std::memcpy(&pdu.Protocol_Family, &enumeration_value.at(location), sizeof(pdu.Protocol_Family));
            return temp;
        case 5:
            std::memcpy(&temp, &pdu.Time_Stamp, sizeof(pdu.Time_Stamp));
            std::memcpy(&pdu.Time_Stamp, &enumeration_value.at(location), sizeof(pdu.Time_Stamp));
            return temp;
        case 6:
            std::memcpy(&temp, &pdu.PDU_Length, sizeof(pdu.PDU_Length));
            std::memcpy(&pdu.PDU_Length, &enumeration_value.at(location), sizeof(pdu.PDU_Length));
            return temp;
        case 7:
            std::memcpy(&temp, &pdu.Padding, sizeof(pdu.Padding));
            std::memcpy(&pdu.Padding, &enumeration_value.at(location), sizeof(pdu.Padding));
            return temp;
        case 8:
            std::memcpy(&temp, &pdu.Site_Identifier, sizeof(pdu.Site_Identifier));
            std::memcpy(&pdu.Site_Identifier, &enumeration_value.at(location), sizeof(pdu.Site_Identifier));
            return temp;
        case 9:
            std::memcpy(&temp, &pdu.Application_Identifier, sizeof(pdu.Application_Identifier));
            std::memcpy(&pdu.Application_Identifier, &enumeration_value.at(location), sizeof(pdu.Application_Identifier));
            return temp;
        case 10:
            std::memcpy(&temp, &pdu.Entity_Identity, sizeof(pdu.Entity_Identity));
            std::memcpy(&pdu.Entity_Identity, &enumeration_value.at(location), sizeof(pdu.Entity_Identity));
            return temp;
        case 11:
            std::memcpy(&temp, &pdu.Force_ID, sizeof(pdu.Force_ID));
            std::memcpy(&pdu.Force_ID, &enumeration_value.at(location), sizeof(pdu.Force_ID));
            return temp;
        case 12:
            std::memcpy(&temp, &pdu.no_Articulation_Parameters, sizeof(pdu.no_Articulation_Parameters));
            std::memcpy(&pdu.no_Articulation_Parameters, &enumeration_value.at(location), sizeof(pdu.no_Articulation_Parameters));
            return temp;
        case 13:
            std::memcpy(&temp, &pdu.Kind, sizeof(pdu.Kind));
            std::memcpy(&pdu.Kind, &enumeration_value.at(location), sizeof(pdu.Kind));
            return temp;
        case 14:
            std::memcpy(&temp, &pdu.Domain, sizeof(pdu.Domain));
            std::memcpy(&pdu.Domain, &enumeration_value.at(location), sizeof(pdu.Domain));
            return temp;
        case 15:
            std::memcpy(&temp, &pdu.Country, sizeof(pdu.Country));
            std::memcpy(&pdu.Country, &enumeration_value.at(location), sizeof(pdu.Country));
            return temp;
        case 16:
            std::memcpy(&temp, &pdu.Category, sizeof(pdu.Category));
            std::memcpy(&pdu.Category, &enumeration_value.at(location), sizeof(pdu.Category));
            return temp;
        case 17:
            std::memcpy(&temp, &pdu.Subcategory, sizeof(pdu.Subcategory));
            std::memcpy(&pdu.Subcategory, &enumeration_value.at(location), sizeof(pdu.Subcategory));
            return temp;
        case 18:
            std::memcpy(&temp, &pdu.Specific, sizeof(pdu.Specific));
            std::memcpy(&pdu.Specific, &enumeration_value.at(location), sizeof(pdu.Specific));
            return temp;
        case 19:
            std::memcpy(&temp, &pdu.Extra, sizeof(pdu.Extra));
            std::memcpy(&pdu.Extra, &enumeration_value.at(location), sizeof(pdu.Extra));
            return temp;
        case 20:
            std::memcpy(&temp, &pdu.Kind_alt, sizeof(pdu.Kind_alt));
            std::memcpy(&pdu.Kind_alt, &enumeration_value.at(location), sizeof(pdu.Kind_alt));
            return temp;
        case 21:
            std::memcpy(&temp, &pdu.Domain_alt, sizeof(pdu.Domain_alt));
            std::memcpy(&pdu.Domain_alt, &enumeration_value.at(location), sizeof(pdu.Domain_alt));
            return temp;
        case 22:
            std::memcpy(&temp, &pdu.Country_alt, sizeof(pdu.Country_alt));
            std::memcpy(&pdu.Country_alt, &enumeration_value.at(location), sizeof(pdu.Country_alt));
            return temp;
        case 23:
            std::memcpy(&temp, &pdu.Category_alt, sizeof(pdu.Category_alt));
            std::memcpy(&pdu.Category_alt, &enumeration_value.at(location), sizeof(pdu.Category_alt));
            return temp;
        case 24:
            std::memcpy(&temp, &pdu.Subcategory_alt, sizeof(pdu.Subcategory_alt));
            std::memcpy(&pdu.Subcategory_alt, &enumeration_value.at(location), sizeof(pdu.Subcategory_alt));
            return temp;
        case 25:
            std::memcpy(&temp, &pdu.Specific_alt, sizeof(pdu.Specific_alt));
            std::memcpy(&pdu.Specific_alt, &enumeration_value.at(location), sizeof(pdu.Specific_alt));
            return temp;
        case 26:
            std::memcpy(&temp, &pdu.Extra_alt, sizeof(pdu.Extra_alt));
            std::memcpy(&pdu.Extra_alt, &enumeration_value.at(location), sizeof(pdu.Extra_alt));
            return temp;
        case 27:
            std::memcpy(&temp, &pdu.LV_First_Vector_Component, sizeof(pdu.LV_First_Vector_Component));
            std::memcpy(&pdu.LV_First_Vector_Component, &enumeration_value.at(location), sizeof(pdu.LV_First_Vector_Component));
            return temp;
        case 28:
            std::memcpy(&temp, &pdu.LV_Second_Vector_Component, sizeof(pdu.LV_Second_Vector_Component));
            std::memcpy(&pdu.LV_Second_Vector_Component, &enumeration_value.at(location), sizeof(pdu.LV_Second_Vector_Component));
            return temp;
        case 29:
            std::memcpy(&temp, &pdu.LV_Third_Vector_Component, sizeof(pdu.LV_Third_Vector_Component));
            std::memcpy(&pdu.LV_Third_Vector_Component, &enumeration_value.at(location), sizeof(pdu.LV_Third_Vector_Component));
            return temp;
        case 30:
            std::memcpy(&temp, &pdu.Entity_x, sizeof(pdu.Entity_x));
            std::memcpy(&pdu.Entity_x, &enumeration_value.at(location), sizeof(pdu.Entity_x));
            return temp;
        case 31:
            std::memcpy(&temp, &pdu.Entity_y, sizeof(pdu.Entity_y));
            std::memcpy(&pdu.Entity_y, &enumeration_value.at(location), sizeof(pdu.Entity_y));
            return temp;
        case 32:
            std::memcpy(&temp, &pdu.Entity_z, sizeof(pdu.Entity_z));
            std::memcpy(&pdu.Entity_z, &enumeration_value.at(location), sizeof(pdu.Entity_z));
            return temp;
        case 33:
            std::memcpy(&temp, &pdu.PSI, sizeof(pdu.PSI));
            std::memcpy(&pdu.PSI, &enumeration_value.at(location), sizeof(pdu.PSI));
            return temp;
        case 34:
            std::memcpy(&temp, &pdu.THETA, sizeof(pdu.THETA));
            std::memcpy(&pdu.THETA, &enumeration_value.at(location), sizeof(pdu.THETA));
            return temp;
        case 35:
            std::memcpy(&temp, &pdu.PHI, sizeof(pdu.PHI));
            std::memcpy(&pdu.PHI, &enumeration_value.at(location), sizeof(pdu.PHI));
            return temp;
        case 36:
            std::memcpy(&temp, &pdu.General_Appearance, sizeof(pdu.General_Appearance));
            std::memcpy(&pdu.General_Appearance, &enumeration_value.at(location), sizeof(pdu.General_Appearance));
            return temp;
        case 37:
            std::memcpy(&temp, &pdu.Appearance_Variant, sizeof(pdu.Appearance_Variant));
            std::memcpy(&pdu.Appearance_Variant, &enumeration_value.at(location), sizeof(pdu.Appearance_Variant));
            return temp;
        case 38:
            std::memcpy(&temp, &pdu.Dead_Reckoning_Algorithm, sizeof(pdu.Dead_Reckoning_Algorithm));
            std::memcpy(&pdu.Dead_Reckoning_Algorithm, &enumeration_value.at(location), sizeof(pdu.Dead_Reckoning_Algorithm));
            return temp;
        case 39:
            std::memcpy(&temp, &pdu.LA_First_Vector, sizeof(pdu.LA_First_Vector));
            std::memcpy(&pdu.LA_First_Vector, &enumeration_value.at(location), sizeof(pdu.LA_First_Vector));
            return temp;
        case 40:
            std::memcpy(&temp, &pdu.LA_Second_Vector, sizeof(pdu.LA_Second_Vector));
            std::memcpy(&pdu.LA_Second_Vector, &enumeration_value.at(location), sizeof(pdu.LA_Second_Vector));
            return temp;
        case 41:
            std::memcpy(&temp, &pdu.LA_Third_Vector, sizeof(pdu.LA_Third_Vector));
            std::memcpy(&pdu.LA_Third_Vector, &enumeration_value.at(location), sizeof(pdu.LA_Third_Vector));
            return temp;
        case 42:
            std::memcpy(&temp, &pdu.Rate_About_X, sizeof(pdu.Rate_About_X));
            std::memcpy(&pdu.Rate_About_X, &enumeration_value.at(location), sizeof(pdu.Rate_About_X));
            return temp;
        case 43:
            std::memcpy(&temp, &pdu.Rate_About_Y, sizeof(pdu.Rate_About_Y));
            std::memcpy(&pdu.Rate_About_Y, &enumeration_value.at(location), sizeof(pdu.Rate_About_Y));
            return temp;
        case 44:
            std::memcpy(&temp, &pdu.Rate_About_Z, sizeof(pdu.Rate_About_Z));
            std::memcpy(&pdu.Rate_About_Z, &enumeration_value.at(location), sizeof(pdu.Rate_About_Z));
            return temp;
        case 45:
            std::memcpy(&temp, &pdu.Entity_Marking_Character_Set, sizeof(pdu.Entity_Marking_Character_Set));
            std::memcpy(&pdu.Entity_Marking_Character_Set, &enumeration_value.at(location), sizeof(pdu.Entity_Marking_Character_Set));
            return temp;
        case 46:
            // WRITE SOMETHING FOR THIS
            return temp;
        case 47:
            std::memcpy(&temp, &pdu.Entity_Capabilities, sizeof(pdu.Entity_Capabilities));
            std::memcpy(&pdu.Entity_Capabilities, &enumeration_value.at(location), sizeof(pdu.Entity_Capabilities));
            return temp;
        case 48:
            std::memcpy(&temp, &pdu.Parameter_Type_Designator, sizeof(pdu.Parameter_Type_Designator));
            std::memcpy(&pdu.Parameter_Type_Designator, &enumeration_value.at(location), sizeof(pdu.Parameter_Type_Designator));
            return temp;
        case 49:
            std::memcpy(&temp, &pdu.Parameter_Change_Indicator, sizeof(pdu.Parameter_Change_Indicator));
            std::memcpy(&pdu.Parameter_Change_Indicator, &enumeration_value.at(location), sizeof(pdu.Parameter_Change_Indicator));
            return temp;
        case 50:
            std::memcpy(&temp, &pdu.Articulation_Attachment_ID, sizeof(pdu.Articulation_Attachment_ID));
            std::memcpy(&pdu.Articulation_Attachment_ID, &enumeration_value.at(location), sizeof(pdu.Articulation_Attachment_ID));
            return temp;
        case 51:
            std::memcpy(&temp, &pdu.Attached_Parts, sizeof(pdu.Attached_Parts));
            std::memcpy(&pdu.Attached_Parts, &enumeration_value.at(location), sizeof(pdu.Attached_Parts));
            return temp;
        case 52:
            std::memcpy(&temp, &pdu.Articulated_Parts_Low, sizeof(pdu.Articulated_Parts_Low));
            std::memcpy(&pdu.Articulated_Parts_Low, &enumeration_value.at(location), sizeof(pdu.Articulated_Parts_Low));
            return temp;
        case 53:
            std::memcpy(&temp, &pdu.Articulated_Parts_High, sizeof(pdu.Articulated_Parts_High));
            std::memcpy(&pdu.Articulated_Parts_High, &enumeration_value.at(location), sizeof(pdu.Articulated_Parts_High));
            return temp;
        case 54:
            std::memcpy(&temp, &pdu.Articulation_Parameter_Value, sizeof(pdu.Articulation_Parameter_Value));
            std::memcpy(&pdu.Articulation_Parameter_Value, &enumeration_value.at(location), sizeof(pdu.Articulation_Parameter_Value));
            return temp;
        }
        return temp;
    }
}

void enumeration_map::edit_pdu(size_t& location, pdu& pdu, std::array<unsigned char, sizeof(double)>& value)
{
    if (enumeration_name.at(location) != 0)
    {
        switch (enumeration_name.at(location))
        {
        case 1:
            std::memcpy(&pdu.Protocol_Version, &value, sizeof(pdu.Protocol_Version));
            break;
        case 2:
            std::memcpy(&pdu.Exercise_Identifier, &value, sizeof(pdu.Exercise_Identifier));
            break;
        case 3:
            std::memcpy(&pdu.PDU_Type, &value, sizeof(pdu.PDU_Type));
            break;
        case 4:
            std::memcpy(&pdu.Protocol_Family, &value, sizeof(pdu.Protocol_Family));
            break;
        case 5:
            std::memcpy(&pdu.Time_Stamp, &value, sizeof(pdu.Time_Stamp));
            break;
        case 6:
            std::memcpy(&pdu.PDU_Length, &value, sizeof(pdu.PDU_Length));
            break;
        case 7:
            std::memcpy(&pdu.Padding, &value, sizeof(pdu.Padding));
            break;
        case 8:
            std::memcpy(&pdu.Site_Identifier, &value, sizeof(pdu.Site_Identifier));
            break;
        case 9:
            std::memcpy(&pdu.Application_Identifier, &value, sizeof(pdu.Application_Identifier));
            break;
        case 10:
            std::memcpy(&pdu.Entity_Identity, &value, sizeof(pdu.Entity_Identity));
            break;
        case 11:
            std::memcpy(&pdu.Force_ID, &value, sizeof(pdu.Force_ID));
            break;
        case 12:
            std::memcpy(&pdu.no_Articulation_Parameters, &value, sizeof(pdu.no_Articulation_Parameters));
            break;
        case 13:
            std::memcpy(&pdu.Kind, &value, sizeof(pdu.Kind));
            break;
        case 14:
            std::memcpy(&pdu.Domain, &value, sizeof(pdu.Domain));
            break;
        case 15:
            std::memcpy(&pdu.Country, &value, sizeof(pdu.Country));
            break;
        case 16:
            std::memcpy(&pdu.Category, &value, sizeof(pdu.Category));
            break;
        case 17:
            std::memcpy(&pdu.Subcategory, &value, sizeof(pdu.Subcategory));
            break;
        case 18:
            std::memcpy(&pdu.Specific, &value, sizeof(pdu.Specific));
            break;
        case 19:
            std::memcpy(&pdu.Extra, &value, sizeof(pdu.Extra));
            break;
        case 20:
            std::memcpy(&pdu.Kind_alt, &value, sizeof(pdu.Kind_alt));
            break;
        case 21:
            std::memcpy(&pdu.Domain_alt, &value, sizeof(pdu.Domain_alt));
            break;
        case 22:
            std::memcpy(&pdu.Country_alt, &value, sizeof(pdu.Country_alt));
            break;
        case 23:
            std::memcpy(&pdu.Category_alt, &value, sizeof(pdu.Category_alt));
            break;
        case 24:
            std::memcpy(&pdu.Subcategory_alt, &value, sizeof(pdu.Subcategory_alt));
            break;
        case 25:
            std::memcpy(&pdu.Specific_alt, &value, sizeof(pdu.Specific_alt));
            break;
        case 26:
            std::memcpy(&pdu.Extra_alt, &value, sizeof(pdu.Extra_alt));
            break;
        case 27:
            std::memcpy(&pdu.LV_First_Vector_Component, &value, sizeof(pdu.LV_First_Vector_Component));
            break;
        case 28:
            std::memcpy(&pdu.LV_Second_Vector_Component, &value, sizeof(pdu.LV_Second_Vector_Component));
            break;
        case 29:
            std::memcpy(&pdu.LV_Third_Vector_Component, &value, sizeof(pdu.LV_Third_Vector_Component));
            break;
        case 30:
            std::memcpy(&pdu.Entity_x, &value, sizeof(pdu.Entity_x));
            break;
        case 31:
            std::memcpy(&pdu.Entity_y, &value, sizeof(pdu.Entity_y));
            break;
        case 32:
            std::memcpy(&pdu.Entity_z, &value, sizeof(pdu.Entity_z));
            break;
        case 33:
            std::memcpy(&pdu.PSI, &value, sizeof(pdu.PSI));
            break;
        case 34:
            std::memcpy(&pdu.THETA, &value, sizeof(pdu.THETA));
            break;
        case 35:
            std::memcpy(&pdu.PHI, &value, sizeof(pdu.PHI));
            break;
        case 36:
            std::memcpy(&pdu.General_Appearance, &value, sizeof(pdu.General_Appearance));
            break;
        case 37:
            std::memcpy(&pdu.Appearance_Variant, &value, sizeof(pdu.Appearance_Variant));
            break;
        case 38:
            std::memcpy(&pdu.Dead_Reckoning_Algorithm, &value, sizeof(pdu.Dead_Reckoning_Algorithm));
            break;
        case 39:
            std::memcpy(&pdu.LA_First_Vector, &value, sizeof(pdu.LA_First_Vector));
            break;
        case 40:
            std::memcpy(&pdu.LA_Second_Vector, &value, sizeof(pdu.LA_Second_Vector));
            break;
        case 41:
            std::memcpy(&pdu.LA_Third_Vector, &value, sizeof(pdu.LA_Third_Vector));
            break;
        case 42:
            std::memcpy(&pdu.Rate_About_X, &value, sizeof(pdu.Rate_About_X));
            break;
        case 43:
            std::memcpy(&pdu.Rate_About_Y, &value, sizeof(pdu.Rate_About_Y));
            break;
        case 44:
            std::memcpy(&pdu.Rate_About_Z, &value, sizeof(pdu.Rate_About_Z));
            break;
        case 45:
            std::memcpy(&pdu.Entity_Marking_Character_Set, &value, sizeof(pdu.Entity_Marking_Character_Set));
            break;
        case 46:
            // WRITE SOMETHING FOR THIS
            break;
        case 47:
            std::memcpy(&pdu.Entity_Capabilities, &value, sizeof(pdu.Entity_Capabilities));
            break;
        case 48:
            std::memcpy(&pdu.Parameter_Type_Designator, &value, sizeof(pdu.Parameter_Type_Designator));
            break;
        case 49:
            std::memcpy(&pdu.Parameter_Change_Indicator, &value, sizeof(pdu.Parameter_Change_Indicator));
            break;
        case 50:
            std::memcpy(&pdu.Articulation_Attachment_ID, &value, sizeof(pdu.Articulation_Attachment_ID));
            break;
        case 51:
            std::memcpy(&pdu.Attached_Parts, &value, sizeof(pdu.Attached_Parts));
            break;
        case 52:
            std::memcpy(&pdu.Articulated_Parts_Low, &value, sizeof(pdu.Articulated_Parts_Low));
            break;
        case 53:
            std::memcpy(&pdu.Articulated_Parts_High, &value, sizeof(pdu.Articulated_Parts_High));
            break;
        case 54:
            std::memcpy(&pdu.Articulation_Parameter_Value, &value, sizeof(pdu.Articulation_Parameter_Value));
            break;
        }
    }
}

#endif