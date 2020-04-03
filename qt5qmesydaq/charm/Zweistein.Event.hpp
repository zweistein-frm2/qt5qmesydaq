/***************************************************************************
 *   Copyright (C) 2019 by Andreas Langhoff <andreas.langhoff@frm2.tum.de> *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation;                                         *
 ***************************************************************************/

#pragma once
#include <random>
#include "Mesytec.hpp"



namespace Zweistein {
	//int _test = 0;
	struct Event {
		enum EventTypeOther {
			RESET=3
		};
		boost::chrono::nanoseconds nanoseconds;
		unsigned short X;
		unsigned short Y;
		unsigned short Amplitude;
		unsigned char type;
		unsigned char ModId;
		Event(Mesy::Mpsd8Event *mpsd8ev,const boost::chrono::nanoseconds &headertime,unsigned short offsetX, Mesy::ModuleId modules[Mpsd8_sizeSLOTS] ) {
			nanoseconds = mpsd8ev->TIMESTAMP()+headertime;
			Amplitude = mpsd8ev->AMPLITUDE();
			Y = Mpsd8_sizeY-  mpsd8ev->POSITION()-1;
			//Y = _test % 1024;
			//_test++;
			type = mpsd8ev->ID();
			ModId = mpsd8ev->MODID();
			
			if (modules[ModId] == Mesy::ModuleId::MPSD8OLD) {
				Amplitude >>= 2;
				Y >>= 2;
			}
			unsigned short slotid = mpsd8ev->SLOTID();
			X = offsetX +  ModId * Mpsd8_sizeSLOTS + slotid;
			/* // generate fast random data
			if (Amplitude == 0) {
				unsigned long l = xor128();
				Amplitude = l >> 16;
				X = l & (unsigned short) (Mcpd8::sizeMCPDID * Mesy::Mpsd8Event::sizeMODID * Mesy::Mpsd8Event::sizeSLOTS - 1);
			}
			*/
			
		}

		Event(Mesy::MdllEvent* mdllev, const boost::chrono::nanoseconds& headertime, unsigned short offsetX, Mesy::ModuleId modules[Mpsd8_sizeSLOTS]) {
			type = mdllev->ID();
			nanoseconds = mdllev->TIMESTAMP() + headertime;
			Amplitude = mdllev->AMPLITUDE();
			Y = Mdll_sizeY - mdllev->YPOSITION()-1;
			X = offsetX+ mdllev->XPOSITION();
		}

		Event():nanoseconds(0),Amplitude(0),X(0),Y(0),type(0),ModId(0){}
		static Event Reset() {
			Event ev;
			ev.type = EventTypeOther::RESET;
			return ev;

		}
	};

	
	

}