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
	//*this = "";
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
	//std::cerr << "zmq::msg::operator=(str)::" << std::endl;
	
	data.clear ();
	data [1] = other;
	
	//std::cerr << std::string (data [1]) << std::endl;
	
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

const bool zmq::msg::is_empty () const
{
	return data.empty ();
}

const bool zmq::msg::is_full () const
{
	return false;
}

const bool zmq::msg::first (frame & f) const
{
	if (is_empty ())
		return false;
	
	f = data [1];
	
	return true;
}

const bool zmq::msg::last (frame & f) const
{
	if (is_empty ())
		return false;
	
	f = data [data.size ()];
	
	return true;
}

const zmq::msg::frame zmq::msg::first (void) const
{
	frame f;
	
	if (!is_empty ())
		f = data [1];
		
	return f;
}

const zmq::msg::frame zmq::msg::last (void) const
{
	frame f;
	
	if (!is_empty ())
		f = data [data.size ()];
		
	return f;
}

const bool zmq::msg::first_rm (void)
{
	if (is_empty ())
		return true;
	
	if (!first_space_fill ())
		return false;
	
	//data.erase (1);
	
	return true;
}

const bool zmq::msg::last_rm (void)
{
	if (is_empty ())
		return true;
	
	data.erase (data.size ());
	
	return true;
}

const bool zmq::msg::first_rm (frame & f)
{
	if (is_empty ())
		return true;
	
	f = data [1];
	//data.erase (1);
	
	if (!first_space_fill ())
		return false;
	
	return true;
}

const bool zmq::msg::last_rm (frame & f)
{
	if (is_empty ())
		return true;
	
	f = data [data.size ()];
	data.erase (data.size ());
	
	return true;
}

const bool zmq::msg::append (const frame & f)
{
	if (is_full ())
		return false;
	
	data [data.size () + 1] = f;
	
	return true;
}

const bool zmq::msg::prepend (const frame & f)
{
	if (is_full ())
		return false;
	
	if (!first_space_clear ())
		return false;
	
	data [1] = f;
	//data.insert_or_assign (1, f);
	
	for (const std::pair <noware::nr, frame> & element : data)
	{
		std::cerr << "zmq::msg::prepend()::data[" << element.first << "]==\"" << std::string (element.second) << "\"" << std::endl;
	}
	
	return true;
}

const bool zmq::msg::first_space_clear (void)
{
	std::cerr << "zmq::msg::first_clear_space()::called" << std::endl;
	if (is_empty ())
	{
		// nothing to do
		std::cerr << "zmq::msg::first_clear_space()::is_empty()==[true]" << std::endl;
		return true;
	}
	std::cerr << "zmq::msg::first_clear_space()::is_empty()==[false]" << std::endl;
	
	if (is_full ())
	{
		std::cerr << "zmq::msg::first_clear_space()::is_full()==[true]" << std::endl;
		// no more space
		return false;
	}
	std::cerr << "zmq::msg::first_clear_space()::is_full()==[false]" << std::endl;
	
	std::map <unsigned int, frame> result;
	//std::string key;
	//std::string key_tmp;
	//frame tmp;
	
	for (const std::pair <unsigned int, frame> & element : data)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		result [element.first + 1] = element.second;
		//result [element.first + 1] = data [element.first];
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//data.erase (0);
	data.clear ();
	for (const std::pair <unsigned int, frame> & element : result)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		data [element.first] = element.second;
		//data [element.first] = result [element.first];
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//result.clear ();
	
	for (const std::pair <unsigned int, frame> & element : data)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		//data [element.first] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
		std::cerr << "zmq::msg::first_clear_space()::data[" << element.first << "]==\"" << std::string (element.second) << "\"" << std::endl;
	}
	
	//std::swap (data, result);
	//data = result
	
	std::cerr << "zmq::msg::first_clear_space()::return" << std::endl;
	return true;
}

const bool zmq::msg::first_space_fill (void)
{
	if (is_empty ())
		// nothing to do
		return true;
	
	//if (is_full ())
	//	// no more space
	//	return false;
	
	std::map <unsigned int, frame> result;
	//std::string key;
	//std::string key_tmp;
	//frame tmp;
	
	for (const std::pair <unsigned int, frame> & element : data)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		result [element.first - 1] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//data.erase (0);
	data.clear ();
	result.erase (0);
	for (const std::pair <unsigned int, frame> & element : result)
	{
		//key = element.first;
		//element.first = "key_tmp";
		
		data [element.first] = element.second;
		//tmp = element.second;
		//data.erase (element.first);
		//data [element.first + 1];
	}
	//result.clear ();
	
	//std::swap (data, result);
	//data = result
	
	return true;
}
