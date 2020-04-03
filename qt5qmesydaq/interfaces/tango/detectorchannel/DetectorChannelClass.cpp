/*----- PROTECTED REGION ID(DetectorChannelClass.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        DetectorChannelClass.cpp
//
// description : C++ source for the DetectorChannelClass.
//               A singleton class derived from DeviceClass.
//               It implements the command and attribute list
//               and all properties and methods required
//               by the DetectorChannel once per process.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <DetectorChannelClass.h>

/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass.cpp

//-------------------------------------------------------------------
/**
 *	Create DetectorChannelClass singleton and
 *	return it in a C function for Python usage
 */
//-------------------------------------------------------------------
extern "C" {
#ifdef _TG_WINDOWS_

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_DetectorChannel_class(const char *name) {
		return DetectorChannel_ns::DetectorChannelClass::init(name);
	}
}

namespace DetectorChannel_ns
{
//===================================================================
//	Initialize pointer for singleton pattern
//===================================================================
DetectorChannelClass *DetectorChannelClass::_instance = NULL;

//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::DetectorChannelClass(string &s)
 * description : 	constructor for the DetectorChannelClass
 *
 * @param s	The class name
 */
//--------------------------------------------------------
DetectorChannelClass::DetectorChannelClass(string &s):MLZDevice_ns::MLZDeviceClass(s)
{
	cout2 << "Entering DetectorChannelClass constructor" << endl;
	set_default_property();
	write_class_property();

	/*----- PROTECTED REGION ID(DetectorChannelClass::constructor) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::constructor

	cout2 << "Leaving DetectorChannelClass constructor" << endl;
}

//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::~DetectorChannelClass()
 * description : 	destructor for the DetectorChannelClass
 */
//--------------------------------------------------------
DetectorChannelClass::~DetectorChannelClass()
{
	/*----- PROTECTED REGION ID(DetectorChannelClass::destructor) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::destructor

	_instance = NULL;
}


//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::init
 * description : 	Create the object if not already done.
 *                  Otherwise, just return a pointer to the object
 *
 * @param	name	The class name
 */
//--------------------------------------------------------
DetectorChannelClass *DetectorChannelClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new DetectorChannelClass(s);
		}
		catch (bad_alloc &)
		{
			throw;
		}
	}
	return _instance;
}

//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::instance
 * description : 	Check if object already created,
 *                  and return a pointer to the object
 */
//--------------------------------------------------------
DetectorChannelClass *DetectorChannelClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}



//===================================================================
//	Command execution method calls
//===================================================================
//--------------------------------------------------------
/**
 * method : 		StartClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *StartClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "StartClass::execute(): arrived" << endl;
	((static_cast<DetectorChannel *>(device))->start());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		StopClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *StopClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "StopClass::execute(): arrived" << endl;
	((static_cast<DetectorChannel *>(device))->stop());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		ClearClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *ClearClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "ClearClass::execute(): arrived" << endl;
	((static_cast<DetectorChannel *>(device))->clear());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		ResumeClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *ResumeClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "ResumeClass::execute(): arrived" << endl;
	((static_cast<DetectorChannel *>(device))->resume());
	return new CORBA::Any();
}

//--------------------------------------------------------
/**
 * method : 		PrepareClass::execute()
 * description : 	method to trigger the execution of the command.
 *
 * @param	device	The device on which the command must be executed
 * @param	in_any	The command input data
 *
 *	returns The command output data (packed in the Any object)
 */
//--------------------------------------------------------
CORBA::Any *PrepareClass::execute(Tango::DeviceImpl *device, TANGO_UNUSED(const CORBA::Any &in_any))
{
	cout2 << "PrepareClass::execute(): arrived" << endl;
	((static_cast<DetectorChannel *>(device))->prepare());
	return new CORBA::Any();
}


//===================================================================
//	Properties management
//===================================================================
//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::get_class_property()
 *	Description : Get the class property for specified name.
 */
//--------------------------------------------------------
Tango::DbDatum DetectorChannelClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, returns  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::get_default_device_property()
 *	Description : Return the default value for device property.
 */
//--------------------------------------------------------
Tango::DbDatum DetectorChannelClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::get_default_class_property()
 *	Description : Return the default value for class property.
 */
//--------------------------------------------------------
Tango::DbDatum DetectorChannelClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}


//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::set_default_property()
 *	Description : Set default property (class and device) for wizard.
 *                For each property, add to wizard property name and description.
 *                If default value has been set, add it to wizard property and
 *                store it in a DbDatum.
 */
//--------------------------------------------------------
void DetectorChannelClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;
	vector<string>	vect_data;

	//	Set Default Class Properties

	//	Set Default device Properties
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::write_class_property()
 *	Description : Set class description fields as property in database
 */
//--------------------------------------------------------
void DetectorChannelClass::write_class_property()
{
	//	First time, check if database used
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("Abstract base class for a detector channel.");
	description << str_desc;
	data.push_back(description);

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("TANGO_BASE_CLASS");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	get_db_class()->put_property(data);
}

//===================================================================
//	Factory methods
//===================================================================

//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::device_factory()
 *	Description : Create the device object(s)
 *                and store them in the device list
 */
//--------------------------------------------------------
void DetectorChannelClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
	/*----- PROTECTED REGION ID(DetectorChannelClass::device_factory_before) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::device_factory_before

	//	Create devices and add it into the device list
	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
		device_list.push_back(new DetectorChannel(this, (*devlist_ptr)[i]));
	}

	//	Manage dynamic attributes if any
	erase_dynamic_attributes(devlist_ptr, get_class_attr()->get_attr_list());

	//	Export devices to the outside world
	for (unsigned long i=1 ; i<=devlist_ptr->length() ; i++)
	{
		//	Add dynamic attributes if any
		DetectorChannel *dev = static_cast<DetectorChannel *>(device_list[device_list.size()-i]);
		dev->add_dynamic_attributes();

		//	Check before if database used.
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(dev);
		else
			export_device(dev, dev->get_name().c_str());
	}

	/*----- PROTECTED REGION ID(DetectorChannelClass::device_factory_after) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::device_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::attribute_factory()
 *	Description : Create the attribute object(s)
 *                and store them in the attribute list
 */
//--------------------------------------------------------
void DetectorChannelClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	/*----- PROTECTED REGION ID(DetectorChannelClass::attribute_factory_before) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::attribute_factory_before
	//	Call atribute_factory for inherited class
	MLZDevice_ns::MLZDeviceClass::attribute_factory(att_list);

	//	Attribute : version - Check if not concrete in inherited class
	Tango::Attr *versionAttr = get_attr_object_by_name(att_list, "version");
	if (versionAttr == NULL)
	{
	}

	//	Attribute : active
	activeAttrib	*active = new activeAttrib();
	Tango::UserDefaultAttrProp	active_prop;
	active_prop.set_description("If this channel can finish the measurement when preselection is reached.");
	//	label	not set for active
	//	unit	not set for active
	//	standard_unit	not set for active
	//	display_unit	not set for active
	//	format	not set for active
	//	max_value	not set for active
	//	min_value	not set for active
	//	max_alarm	not set for active
	//	min_alarm	not set for active
	//	max_warning	not set for active
	//	min_warning	not set for active
	//	delta_t	not set for active
	//	delta_val	not set for active
	
	active->set_default_properties(active_prop);
	//	Not Polled
	active->set_disp_level(Tango::OPERATOR);
	//	Not Memorized
	att_list.push_back(active);


	//	Create a list of static attributes
	create_static_attribute_list(get_class_attr()->get_attr_list());
	/*----- PROTECTED REGION ID(DetectorChannelClass::attribute_factory_after) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::attribute_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::pipe_factory()
 *	Description : Create the pipe object(s)
 *                and store them in the pipe list
 */
//--------------------------------------------------------
void DetectorChannelClass::pipe_factory()
{
	/*----- PROTECTED REGION ID(DetectorChannelClass::pipe_factory_before) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::pipe_factory_before
	/*----- PROTECTED REGION ID(DetectorChannelClass::pipe_factory_after) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::pipe_factory_after
}
//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::command_factory()
 *	Description : Create the command object(s)
 *                and store them in the command list
 */
//--------------------------------------------------------
void DetectorChannelClass::command_factory()
{
	/*----- PROTECTED REGION ID(DetectorChannelClass::command_factory_before) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::command_factory_before
	//	Call command_factory for inherited class
	MLZDevice_ns::MLZDeviceClass::command_factory();








	//	Command Start
	StartClass	*pStartCmd =
		new StartClass("Start",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pStartCmd);

	//	Command Stop
	StopClass	*pStopCmd =
		new StopClass("Stop",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pStopCmd);

	//	Command Clear
	ClearClass	*pClearCmd =
		new ClearClass("Clear",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pClearCmd);

	//	Command Resume
	ResumeClass	*pResumeCmd =
		new ResumeClass("Resume",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pResumeCmd);

	//	Command Prepare
	PrepareClass	*pPrepareCmd =
		new PrepareClass("Prepare",
			Tango::DEV_VOID, Tango::DEV_VOID,
			"",
			"",
			Tango::OPERATOR);
	command_list.push_back(pPrepareCmd);

	/*----- PROTECTED REGION ID(DetectorChannelClass::command_factory_after) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::command_factory_after
}

//===================================================================
//	Dynamic attributes related methods
//===================================================================

//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::create_static_attribute_list
 * description : 	Create the a list of static attributes
 *
 * @param	att_list	the ceated attribute list
 */
//--------------------------------------------------------
void DetectorChannelClass::create_static_attribute_list(vector<Tango::Attr *> &att_list)
{
	for (unsigned long i=0 ; i<att_list.size() ; i++)
	{
		string att_name(att_list[i]->get_name());
		transform(att_name.begin(), att_name.end(), att_name.begin(), ::tolower);
		defaultAttList.push_back(att_name);
	}

	cout2 << defaultAttList.size() << " attributes in default list" << endl;

	/*----- PROTECTED REGION ID(DetectorChannelClass::create_static_att_list) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::create_static_att_list
}


//--------------------------------------------------------
/**
 * method : 		DetectorChannelClass::erase_dynamic_attributes
 * description : 	delete the dynamic attributes if any.
 *
 * @param	devlist_ptr	the device list pointer
 * @param	list of all attributes
 */
//--------------------------------------------------------
void DetectorChannelClass::erase_dynamic_attributes(const Tango::DevVarStringArray *devlist_ptr, vector<Tango::Attr *> &att_list)
{
	Tango::Util *tg = Tango::Util::instance();

	for (unsigned long i=0 ; i<devlist_ptr->length() ; i++)
	{
		Tango::DeviceImpl *dev_impl = tg->get_device_by_name(((string)(*devlist_ptr)[i]).c_str());
		DetectorChannel *dev = static_cast<DetectorChannel *> (dev_impl);

		vector<Tango::Attribute *> &dev_att_list = dev->get_device_attr()->get_attribute_list();
		vector<Tango::Attribute *>::iterator ite_att;
		for (ite_att=dev_att_list.begin() ; ite_att != dev_att_list.end() ; ++ite_att)
		{
			string att_name((*ite_att)->get_name_lower());
			if ((att_name == "state") || (att_name == "status"))
				continue;
			vector<string>::iterator ite_str = find(defaultAttList.begin(), defaultAttList.end(), att_name);
			if (ite_str == defaultAttList.end())
			{
				cout2 << att_name << " is a UNWANTED dynamic attribute for device " << (*devlist_ptr)[i] << endl;
				Tango::Attribute &att = dev->get_device_attr()->get_attr_by_name(att_name.c_str());
				dev->remove_attribute(att_list[att.get_attr_idx()], true, false);
				--ite_att;
			}
		}
	}
	/*----- PROTECTED REGION ID(DetectorChannelClass::erase_dynamic_attributes) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::erase_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannelClass::get_attr_by_name()
 *	Description : returns Tango::Attr * object found by name
 */
//--------------------------------------------------------
Tango::Attr *DetectorChannelClass::get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname)
{
	vector<Tango::Attr *>::iterator it;
	for (it=att_list.begin() ; it<att_list.end() ; ++it)
		if ((*it)->get_name()==attname)
			return (*it);
	//	Attr does not exist
	return NULL;
}


/*----- PROTECTED REGION ID(DetectorChannelClass::Additional Methods) ENABLED START -----*/

/*----- PROTECTED REGION END -----*/	//	DetectorChannelClass::Additional Methods
} //	namespace