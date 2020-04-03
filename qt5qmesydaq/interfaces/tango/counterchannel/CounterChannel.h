/*----- PROTECTED REGION ID(CounterChannel.h) ENABLED START -----*/
//=============================================================================
//
// file :        CounterChannel.h
//
// description : Include file for the CounterChannel class
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


#ifndef CounterChannel_H
#define CounterChannel_H

#include <tango.h>
#include "../mlzdevice/MLZDevice.h"
#include "../detectorchannel/DetectorChannel.h"


/*----- PROTECTED REGION END -----*/	//	CounterChannel.h

/**
 *  CounterChannel class description:
 *    Base class for channels that control monitor or single detector counts.
 */

namespace CounterChannel_ns
{
/*----- PROTECTED REGION ID(CounterChannel::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	CounterChannel::Additional Class Declarations

class CounterChannel : public DetectorChannel_ns::DetectorChannel
{

/*----- PROTECTED REGION ID(CounterChannel::Data Members) ENABLED START -----*/

//	Add your own data members

//	Device property data members
public:
	//	channel:	What monitor input is used.
	Tango::DevUShort	channel;

/*----- PROTECTED REGION END -----*/	//	CounterChannel::Data Members


//	Attribute data members
public:
	Tango::DevULong64	*attr_value_read;
	Tango::DevULong64	*attr_preselection_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	CounterChannel(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	CounterChannel(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	CounterChannel(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~CounterChannel() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : CounterChannel::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);
	//--------------------------------------------------------
	/*
	 *	Method      : CounterChannel::write_attr_hardware()
	 *	Description : Hardware writing for attributes.
	 */
	//--------------------------------------------------------
	virtual void write_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute value related methods
 *	Description: Current counter value.
 *
 *	Data type:	Tango::DevULong64
 *	Attr type:	Scalar
 */
	virtual void read_value(Tango::Attribute &attr);
	virtual bool is_value_allowed(Tango::AttReqType type);
/**
 *	Attribute preselection related methods
 *	Description: Current preset value.
 *
 *	Data type:	Tango::DevULong64
 *	Attr type:	Scalar
 */
	virtual void read_preselection(Tango::Attribute &attr);
	virtual void write_preselection(Tango::WAttribute &attr);
	virtual bool is_preselection_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : CounterChannel::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:


	//--------------------------------------------------------
	/**
	 *	Method      : CounterChannel::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(CounterChannel::Additional Method prototypes) ENABLED START -----*/
//	Additional Method prototypes

	virtual void read_active(Tango::Attribute &attr);

	virtual void write_active(Tango::WAttribute &attr);

	virtual Tango::DevVarStringArray *get_properties();

protected:
	virtual bool isMaster(void);

/*----- PROTECTED REGION END -----*/	//	CounterChannel::Additional Method prototypes
};

/*----- PROTECTED REGION ID(CounterChannel::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	CounterChannel::Additional Classes Definitions

}	//	End of namespace

#endif   //	CounterChannel_H