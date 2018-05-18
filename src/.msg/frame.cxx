#pragma once

//#include "frame.hxx"

zmq::msg::frame::frame (void)
{
}

zmq::msg::frame::frame (const frame & other)
{
	*this = other;
}

zmq::msg::frame::frame (const zframe_t * other)
{
	*this = other;
}

zmq::msg::frame::frame (const zmq::message_t & other)
{
	*this = other;
}

zmq::msg::frame::frame (const zmq_msg_t * other)
{
	*this = other;
}

zmq::msg::frame::frame (const std::string & other)
{
	*this = other;
}

zmq::msg::frame::~frame (void)
{
	//fin ();
}

zmq::msg::frame::operator const zframe_t * (void) const
{
	zframe_t * frame;
	
	frame = zframe_new (data.data (), data.size ());
	
	//assert (frame);
	//assert (zframe_is (frame));
	//assert (frame -> tag == ZFRAME_TAG);
	
	return frame;
}

zmq::msg::frame::operator const zmq::message_t & (void) const
{
	return data;
}

zmq::msg::frame::operator zmq::message_t & (void)
{
	return data;
}

zmq::msg::frame::operator const zmq_msg_t * (void) const
{
	zmq_msg_t * msg;
	
	zmq_msg_init_data (msg, data.data (), data.size (), zmq::msg::frame::free, nullptr);
	
	return msg;
}

zmq::msg::frame::operator const std::string (void) const
{
	//std::cerr << "zmq::msg::frame::operator str()::" << std::endl;
	////std::string test;
	////test = static_cast <const char *> (data.data ()), data.size ();
	//std::cerr << static_cast <const char *> (data.data ()) << std::endl;
	//return std::string ("22 serialization::archive 15 0 0 1 0 0 0 7 subject 9 magnitude");
	return std::string (static_cast <const char *> (data.data ()), data.size ());
}

const zmq::msg::frame & zmq::msg::frame::operator = (const frame & other)
{
	//data = other.data;
	data.copy (&(other.data));
	
	return other;
}

const zframe_t * zmq::msg::frame::operator = (const zframe_t * other)
{
	data.rebuild (zframe_data (other), zframe_size (other));
	
	return other;
}

const zmq::message_t & zmq::msg::frame::operator = (const zmq::message_t & other)
{
	//data = other;
	data.copy (&other);
	
	return data;
}

const zmq_msg_t * zmq::msg::frame::operator = (const zmq_msg_t * other)
{
	data.rebuild (zmq_msg_data (other), zmq_msg_size (other));
	
	return other;
}

const std::string & zmq::msg::frame::operator = (const std::string & other)
{
	//std::cerr << "zmq::msg::frame::operator=(str)::" << std::endl;
	
	data.rebuild (other.size ());
	std::memcpy (data.data (), other.data (), other.size ());
	
	return other;
}

const bool zmq::msg::frame::operator == (const frame & other) const
{
	return data.equal (&(other.data));
}

const bool zmq::msg::frame::operator == (const zframe_t * other) const
{
	return *this == frame (other);
}

const bool zmq::msg::frame::operator == (const zmq::message_t & other) const
{
	return *this == frame (other);
}

const bool zmq::msg::frame::operator == (const zmq_msg_t * other) const
{
	return *this == frame (other);
}

const bool zmq::msg::frame::operator == (const std::string & other) const
{
	return *this == frame (other);
}

const bool zmq::msg::frame::operator != (const frame & other) const
{
	return data.equal (&(other.data));
}

const bool zmq::msg::frame::operator != (const zframe_t * other) const
{
	return !(*this == other);
}

const bool zmq::msg::frame::operator != (const zmq::message_t & other) const
{
	return !(*this == other);
}

const bool zmq::msg::frame::operator != (const zmq_msg_t * other) const
{
	return !(*this == other);
}

const bool zmq::msg::frame::operator != (const std::string & other) const
{
	return !(*this == other);
}

void zmq::msg::frame::free (void * data, void * hint)
{
	::free (data);
}
