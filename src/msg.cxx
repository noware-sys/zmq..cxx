#pragma once

#include "msg.hxx"
#include ".msg/incl.cxx"
#include ".msg/.cxx"

#include <zmq.hpp>
#include <czmq.h>
#include <zmsg.c>

#include <noware/nr.cxx>

#include <string>
#include <iostream>
//#include "frame.cxx"

//#pragma once

//#include "frame.hxx"

zmq::msg::msg (void)
{
	init ();
}

zmq::msg::msg (const msg & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zmsg_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const frame & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zframe_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const message_t & other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const zmq_msg_t * other)
{
	init ();
	*this = other;
}

zmq::msg::msg (const std::string & other)
{
	init ();
	*this = other;
}

zmq::msg::~msg (void)
{
	fin ();
}

const bool zmq::msg::fin (void)
{
}

const bool zmq::msg::init (void)
{
}

zmq::msg::operator const zmsg_t * (void) const
{
	zmsg_t * msg;
	zframe_t * frame_p;
	zframe_t ** frame_pp;
	
	msg = zmsg_new ();
	//frame = zframe_new_empty ();
	
	for (const std::pair <noware::nr, zmq::msg::frame> & _frame : data)
	{
		//zframe_reset (_frame, );
		//frame_p = (zframe_t *) _frame.second;
		frame_p = _frame.second.operator const zframe_t * ();
		frame_pp = &frame_p;
		
		//assert (zframe_is (*frame_pp));
		//assert ((*frame_pp) -> tag == ZFRAME_TAG);
		
		zmsg_append (msg, frame_pp);
	}
	
	return msg;
}

zmq::msg::operator const frame & (void) const
{
	return data [1];
}

zmq::msg::operator const zframe_t * (void) const
{
	return data [1];
}

zmq::msg::operator const message_t & (void) const
{
	//return data [1].operator const message_t & ();
	return data [1];
}

zmq::msg::operator message_t & (void)
{
	//return data [1].operator message_t & ();
	return data [1];
}

zmq::msg::operator const zmq_msg_t * (void) const
{
	return data [1];
}

zmq::msg::operator const std::string (void) const
{
	return data [1];
}

const zmq::msg & zmq::msg::operator = (const msg & other)
{
	data = other.data;
	
	return other;
}

const zmsg_t * zmq::msg::operator = (const zmsg_t * other)
{
	zframe_t * frm;
	noware::nr ndx;
	
	data.clear ();
	frm = zmsg_first (other);
	ndx = 1;
	while (frm != nullptr)
	{
		// This makes a copy of the frame.
		data [ndx] = frm;
		
		//zframe_destroy (&f);
		
		frm = zmsg_next (other);
		++ndx;
	}
	
	return other;
}

const zmq::msg::frame & zmq::msg::operator = (const frame & other)
{
	data.clear ();
	data [1] = other;
	
	return other;
}

const zframe_t * zmq::msg::operator = (const zframe_t * other)
{
	data.clear ();
	data [1] = other;
	
	return other;
}

const zmq::message_t & zmq::msg::operator = (const message_t & other)
{
	data.clear ();
	data [1] = other;
	
	return other;
}

const zmq_msg_t * zmq::msg::operator = (const zmq_msg_t * other)
{
	data.clear ();
	data [1] = other;
	
	return other;
}

const std::string & zmq::msg::operator = (const std::string & other)
{
	//std::cout << "zmq::msg::operator=(str)::" << std::endl;
	
	data.clear ();
	data [1] = other;
	
	//std::cout << std::string (data [1]) << std::endl;
	
	return other;
}

const bool zmq::msg::operator == (const msg & other) const
{
	return data == other.data;
}

const bool zmq::msg::operator == (const zmsg_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const frame & other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const zframe_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const message_t & other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const zmq_msg_t * other) const
{
	return *this == msg (other);
}

const bool zmq::msg::operator == (const std::string & other) const
{
	return *this == msg (other);
}
