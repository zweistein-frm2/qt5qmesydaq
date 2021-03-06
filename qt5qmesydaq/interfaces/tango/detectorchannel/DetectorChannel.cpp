/*----- PROTECTED REGION ID(DetectorChannel.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        DetectorChannel.cpp
//
// description : C++ source for the DetectorChannel class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               DetectorChannel are implemented in this file.
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


#include <DetectorChannel.h>
#include <DetectorChannelClass.h>

#include "MultipleLoopApplication.h"
#include "QMesydaqDetectorInterface.h"

/*----- PROTECTED REGION END -----*/	//	DetectorChannel.cpp

/**
 *  DetectorChannel class description:
 *    Abstract base class for a detector channel.
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name   |  Method name
//================================================================
//  State          |  Inherited (no method)
//  Status         |  Inherited (no method)
//  On             |  Inherited (no method)
//  Off            |  Inherited (no method)
//  GetProperties  |  Inherited (no method)
//  SetProperties  |  Inherited (no method)
//  Reset          |  Inherited (no method)
//  Start          |  start
//  Stop           |  stop
//  Clear          |  clear
//  Resume         |  resume
//  Prepare        |  prepare
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  version  |  Tango::DevString	Scalar
//  active   |  Tango::DevBoolean	Scalar
//================================================================

namespace DetectorChannel_ns
{
/*----- PROTECTED REGION ID(DetectorChannel::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	DetectorChannel::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::DetectorChannel()
 *	Description : Constructors for a Tango device
 *                implementing the classDetectorChannel
 */
//--------------------------------------------------------
DetectorChannel::DetectorChannel(Tango::DeviceClass *cl, string &s)
 : MLZDevice(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(DetectorChannel::constructor_1) ENABLED START -----*/
	init_device();

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::constructor_1
}
//--------------------------------------------------------
DetectorChannel::DetectorChannel(Tango::DeviceClass *cl, const char *s)
 : MLZDevice(cl, s)
{
	/*----- PROTECTED REGION ID(DetectorChannel::constructor_2) ENABLED START -----*/
	init_device();

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::constructor_2
}
//--------------------------------------------------------
DetectorChannel::DetectorChannel(Tango::DeviceClass *cl, const char *s, const char *d)
 : MLZDevice(cl, s, d)
{
	/*----- PROTECTED REGION ID(DetectorChannel::constructor_3) ENABLED START -----*/
	init_device();

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void DetectorChannel::delete_device()
{
	DEBUG_STREAM << "DetectorChannel::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::delete_device) ENABLED START -----*/

	//	Delete device allocated objects

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::delete_device
	delete[] attr_active_read;

	if (Tango::Util::instance()->is_svr_shutting_down()==false  &&
		Tango::Util::instance()->is_device_restarting(device_name)==false &&
		Tango::Util::instance()->is_svr_starting()==false)
	{
		//	If not shutting down call delete device for inherited object
		MLZDevice_ns::MLZDevice::delete_device();
	}
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void DetectorChannel::init_device()
{
	DEBUG_STREAM << "DetectorChannel::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::init_device_before) ENABLED START -----*/

	MultipleLoopApplication *app = dynamic_cast<MultipleLoopApplication *>(QApplication::instance());
	if (app)
		m_interface = dynamic_cast<QMesyDAQDetectorInterface *>(app->getQtInterface());
	else
		m_interface = NULL;
	//	Initialization before get_device_property() call

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::init_device_before
	
	if (Tango::Util::instance()->is_svr_starting() == false  &&
		Tango::Util::instance()->is_device_restarting(device_name)==false)
	{
		//	If not starting up call init device for inherited object
		MLZDevice_ns::MLZDevice::init_device();
	}
	//	No device property to be read from database
	
	attr_active_read = new Tango::DevBoolean[1];
	/*----- PROTECTED REGION ID(DetectorChannel::init_device) ENABLED START -----*/

	//	Initialize device
	attr_active_read[0] = false;

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::init_device
}


//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void DetectorChannel::always_executed_hook()
{
	DEBUG_STREAM << "DetectorChannel::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::always_executed_hook) ENABLED START -----*/

	//	code always executed before all requests

	if (!m_interface)
		set_state(Tango::FAULT);

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void DetectorChannel::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "DetectorChannel::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::read_attr_hardware) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void DetectorChannel::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "DetectorChannel::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::write_attr_hardware) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute active related method
 *	Description: If this channel can finish the measurement when preselection is reached.
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void DetectorChannel::read_active(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DetectorChannel::read_active(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::read_active) ENABLED START -----*/
	//	Set the attribute value
	attr.set_value(attr_active_read);

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::read_active
}
//--------------------------------------------------------
/**
 *	Write attribute active related method
 *	Description: If this channel can finish the measurement when preselection is reached.
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void DetectorChannel::write_active(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "DetectorChannel::write_active(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevBoolean	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(DetectorChannel::write_active) ENABLED START -----*/


	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::write_active
}

//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void DetectorChannel::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(DetectorChannel::add_dynamic_attributes) ENABLED START -----*/

	//	Add your own code to create and add dynamic attributes if any

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command Start related method
 *	Description: Starts the acquisition.
 *
 */
//--------------------------------------------------------
void DetectorChannel::start()
{
	DEBUG_STREAM << "DetectorChannel::Start()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::start) ENABLED START -----*/
	//	Add your own code
	if (!m_interface)
		::Tango::Except::throw_exception("Runtime error",
						 "Control interface not initialized",
						 "DetectorChannel::start()");

	if (isMaster() && get_state() != ::Tango::MOVING)
	{
		m_started = true;
		set_state(Tango::MOVING);
#if 0
		m_interface->setListMode(m_writeListmode, true);
		if (m_writeListmode)
		{
			m_listFilename = incNumber(m_listFilename);
			updateResource<std::string>("lastlistfile", m_listFilename);
			m_interface->setListFileName(m_listFilename.c_str());
		}

		m_interface->setHistogramMode(m_writeHistogram);
		if (m_writeHistogram)
		{
			m_histFilename = incNumber(m_histFilename);
			updateResource<std::string>("lasthistfile", m_histFilename);
			m_interface->setHistogramFileName(m_histFilename.c_str());
		}
#endif
		ERROR_STREAM << "interface::start()";
		m_interface->start();
		for (int i = 0; i < 10; ++i)
		{
			usleep(300000);
			if (m_interface->status())
				break;
		}
		m_started = false;
	}

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::start
}
//--------------------------------------------------------
/**
 *	Command Stop related method
 *	Description: Stops a running acquisition.
 *
 */
//--------------------------------------------------------
void DetectorChannel::stop()
{
	DEBUG_STREAM << "DetectorChannel::Stop()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::stop) ENABLED START -----*/
	//	Add your own code
	if (!m_interface)
		::Tango::Except::throw_exception("Runtime error",
						 "Control interface not initialized",
						 "DetectorChannel::stop()");
	if (isMaster() && get_state() == Tango::MOVING)
		m_interface->stop();

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::stop
}
//--------------------------------------------------------
/**
 *	Command Clear related method
 *	Description: Clears all values of the detector.
 *
 */
//--------------------------------------------------------
void DetectorChannel::clear()
{
	DEBUG_STREAM << "DetectorChannel::Clear()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::clear) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::clear
}
//--------------------------------------------------------
/**
 *	Command Resume related method
 *	Description: Resumes a stopped data aquisition.
 *
 */
//--------------------------------------------------------
void DetectorChannel::resume()
{
	DEBUG_STREAM << "DetectorChannel::Resume()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::resume) ENABLED START -----*/

	//	Add your own code
	start();

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::resume
}
//--------------------------------------------------------
/**
 *	Command Prepare related method
 *	Description: Prepares the acquisition, so that a Start command can start it immediately.
 *
 */
//--------------------------------------------------------
void DetectorChannel::prepare()
{
	DEBUG_STREAM << "DetectorChannel::Prepare()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DetectorChannel::prepare) ENABLED START -----*/

	//	Add your own code

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::prepare
}
//--------------------------------------------------------
/**
 *	Method      : DetectorChannel::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void DetectorChannel::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(DetectorChannel::add_dynamic_commands) ENABLED START -----*/

	//	Add your own code to create and add dynamic commands if any

	/*----- PROTECTED REGION END -----*/	//	DetectorChannel::add_dynamic_commands
}

/*----- PROTECTED REGION ID(DetectorChannel::namespace_ending) ENABLED START -----*/

//	Additional Methods
bool DetectorChannel::isMaster(void)
{
	return false;
}

Tango::DevState DetectorChannel::dev_state()
{
	Tango::DevState tmp(Tango::ON);
	switch (m_interface->status() | m_started)
	{
		case 1 :
			tmp = ::Tango::MOVING;
			break;
		case 0 :
		default:
			break;
	}
	set_state(tmp);
	return tmp;
}

/*----- PROTECTED REGION END -----*/	//	DetectorChannel::namespace_ending
} //	namespace
