
# DIS APPOINTMENT V0.3
BETA   

Routes Distributed Interactive Simulation [DIS](https://en.wikipedia.org/wiki/Distributed_Interactive_Simulation) traffic over different network ports with the option to alter mappings of PDU's that meet custom criteria to facilitate different simulations applications that may have units mapped differently. 
   

## Notes
**THIS CODE SUCKS
Please do not take this as an example of work I would consider good, it needs a lot of work to be modularized so I can perform unit testing on each component and re build it in a way that promotes a more comfortable environment to build upon.**
Currently only reads Entity State PDUs   
Currently only manipulates INT values   
   
TODO   
-Add if statements when grabbing stream to check header for type of PDU, this should enable usage of other PDU types   
-Clean up config read method/file to be more user friendly (csv or xml)   
-Add manipulation functionality to all data types within PDU while maintaining ability to store them back in buffer to send back over network without altering size   
Use DIS data [dictionary](http://faculty.nps.edu/brutzman/vrtp/mil/navy/nps/disEnumerations/JdbeHtmlFiles/dis-dd.html) for reference   

## Instructions
### Initialize
First line: 	listening port (int eg:3000)   
Second line: 	number of sending addresses (int eg:2)   
   
### Set up send addresses
For each address   
First line: 	port number (int eg:3001)   
Second line: 	ip address (string eg:192.168.0.255)   
Third line:	number of enumerations to change (int)   
If third line > 0   
	Fourth line:	How many flags to check (INT)   
	If fourth line > 0   
		Fifth line: 	enumeration flag name to check (Enumeration list below with value to left)   
		Sixth line:	enumeration flag value to check   
		etc.. repeat for each flag   
	~Seventh line: 	enumeration to change   
	~Eightth line:	value to change to   
	etc.. repeat for each port   
   
### Enumerations list
0    No_change,    
1    Protocol_Version,		// 8    
2    Exercise_Identifier,	// 8    
3    PDU_Type,			    // 8   
4    Protocol_Family,		// 8   
5    Time_Stamp,		// 32   
6    PDU_Length,		// 16   
7    Padding,			// 16   
8    Site_Identifier,		// 16      
9    Application_Identifier, 	// 16     
10    Entity_Identity,		// 16   
11    Force_ID,			// 8
12    no_Articulation_Parameters,	// 8   
13    Kind,		// 8   
14    Domain,		// 8    
15    Country,		// 16   
16    Category,		// 8   
17    Subcategory,	// 8   
18    Specific,		// 8   
19    Extra,		// 8   
20    Kind_alt,		// 8   
21    Domain_alt,	// 8   
22    Country_alt,	// 16   
23    Category_alt,	// 8   
24    Subcategory_alt,	// 8   
25    Specific_alt,	// 8   
26    Extra_alt,	// 8   
27    LV_First_Vector_Component,	// 32   
28    LV_Second_Vector_Component,	// 32   
29    LV_Third_Vector_Component,	// 32   
30    Entity_x,	// 64   
31    Entity_y,	// 64   
32    Entity_z,	// 64   
33    PSI,	    // 32   
34    THETA,	// 32   
35    PHI,	    // 32   
36    General_Appearance,	    // 16   
37    Appearance_Variant,       // 16   
38    Dead_Reckoning_Algorithm,	// 8 ENUMERATION   
39    LA_First_Vector,	// 32   
40    LA_Second_Vector,	// 32   
41    LA_Third_Vector,	// 32   
42    Rate_About_X,		// 32   
43    Rate_About_Y,		// 32   
44    Rate_About_Z,		// 32   
45    Entity_Marking_Character_Set,	// 8 ENUMERATION   
46    Marking,			    // 88   
47    Entity_Capabilities,	// 8   
48    Parameter_Type_Designator,	// 8   
49    Parameter_Change_Indicator,	// 8   
50    Articulation_Attachment_ID,	// 16   
51    Attached_Parts,			    // 32 ENUMERATION   
52    Articulated_Parts_Low,		// 16 BITFIELD   
53    Articulated_Parts_High,		// 16 BITFIELD   
54    Articulation_Parameter_Value	// 64   
