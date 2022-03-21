#ifndef _ROS_warthog_msgs_Status_h
#define _ROS_warthog_msgs_Status_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ros/duration.h"

namespace warthog_msgs
{

  class Status : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _hardware_id_type;
      _hardware_id_type hardware_id;
      typedef ros::Duration _mcu_uptime_type;
      _mcu_uptime_type mcu_uptime;
      typedef ros::Duration _connection_uptime_type;
      _connection_uptime_type connection_uptime;
      typedef float _mcu_temperature_type;
      _mcu_temperature_type mcu_temperature;
      typedef bool _stop_engaged_type;
      _stop_engaged_type stop_engaged;
      typedef float _measured_battery_type;
      _measured_battery_type measured_battery;
      typedef float _measured_48v_type;
      _measured_48v_type measured_48v;
      typedef float _measured_24v_type;
      _measured_24v_type measured_24v;
      typedef float _measured_12v_type;
      _measured_12v_type measured_12v;
      typedef float _current_battery_type;
      _current_battery_type current_battery;
      typedef float _current_48v_type;
      _current_48v_type current_48v;
      typedef float _current_24v_type;
      _current_24v_type current_24v;
      typedef float _current_12v_type;
      _current_12v_type current_12v;
      typedef float _current_computer_type;
      _current_computer_type current_computer;
      typedef float _current_battery_peak_type;
      _current_battery_peak_type current_battery_peak;
      typedef float _total_power_consumed_type;
      _total_power_consumed_type total_power_consumed;

    Status():
      header(),
      hardware_id(""),
      mcu_uptime(),
      connection_uptime(),
      mcu_temperature(0),
      stop_engaged(0),
      measured_battery(0),
      measured_48v(0),
      measured_24v(0),
      measured_12v(0),
      current_battery(0),
      current_48v(0),
      current_24v(0),
      current_12v(0),
      current_computer(0),
      current_battery_peak(0),
      total_power_consumed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_hardware_id = strlen(this->hardware_id);
      varToArr(outbuffer + offset, length_hardware_id);
      offset += 4;
      memcpy(outbuffer + offset, this->hardware_id, length_hardware_id);
      offset += length_hardware_id;
      *(outbuffer + offset + 0) = (this->mcu_uptime.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->mcu_uptime.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->mcu_uptime.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->mcu_uptime.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mcu_uptime.sec);
      *(outbuffer + offset + 0) = (this->mcu_uptime.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->mcu_uptime.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->mcu_uptime.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->mcu_uptime.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mcu_uptime.nsec);
      *(outbuffer + offset + 0) = (this->connection_uptime.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->connection_uptime.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->connection_uptime.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->connection_uptime.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->connection_uptime.sec);
      *(outbuffer + offset + 0) = (this->connection_uptime.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->connection_uptime.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->connection_uptime.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->connection_uptime.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->connection_uptime.nsec);
      union {
        float real;
        uint32_t base;
      } u_mcu_temperature;
      u_mcu_temperature.real = this->mcu_temperature;
      *(outbuffer + offset + 0) = (u_mcu_temperature.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mcu_temperature.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mcu_temperature.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mcu_temperature.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mcu_temperature);
      union {
        bool real;
        uint8_t base;
      } u_stop_engaged;
      u_stop_engaged.real = this->stop_engaged;
      *(outbuffer + offset + 0) = (u_stop_engaged.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stop_engaged);
      union {
        float real;
        uint32_t base;
      } u_measured_battery;
      u_measured_battery.real = this->measured_battery;
      *(outbuffer + offset + 0) = (u_measured_battery.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_measured_battery.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_measured_battery.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_measured_battery.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->measured_battery);
      union {
        float real;
        uint32_t base;
      } u_measured_48v;
      u_measured_48v.real = this->measured_48v;
      *(outbuffer + offset + 0) = (u_measured_48v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_measured_48v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_measured_48v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_measured_48v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->measured_48v);
      union {
        float real;
        uint32_t base;
      } u_measured_24v;
      u_measured_24v.real = this->measured_24v;
      *(outbuffer + offset + 0) = (u_measured_24v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_measured_24v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_measured_24v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_measured_24v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->measured_24v);
      union {
        float real;
        uint32_t base;
      } u_measured_12v;
      u_measured_12v.real = this->measured_12v;
      *(outbuffer + offset + 0) = (u_measured_12v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_measured_12v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_measured_12v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_measured_12v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->measured_12v);
      union {
        float real;
        uint32_t base;
      } u_current_battery;
      u_current_battery.real = this->current_battery;
      *(outbuffer + offset + 0) = (u_current_battery.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_battery.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_battery.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_battery.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_battery);
      union {
        float real;
        uint32_t base;
      } u_current_48v;
      u_current_48v.real = this->current_48v;
      *(outbuffer + offset + 0) = (u_current_48v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_48v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_48v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_48v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_48v);
      union {
        float real;
        uint32_t base;
      } u_current_24v;
      u_current_24v.real = this->current_24v;
      *(outbuffer + offset + 0) = (u_current_24v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_24v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_24v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_24v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_24v);
      union {
        float real;
        uint32_t base;
      } u_current_12v;
      u_current_12v.real = this->current_12v;
      *(outbuffer + offset + 0) = (u_current_12v.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_12v.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_12v.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_12v.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_12v);
      union {
        float real;
        uint32_t base;
      } u_current_computer;
      u_current_computer.real = this->current_computer;
      *(outbuffer + offset + 0) = (u_current_computer.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_computer.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_computer.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_computer.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_computer);
      union {
        float real;
        uint32_t base;
      } u_current_battery_peak;
      u_current_battery_peak.real = this->current_battery_peak;
      *(outbuffer + offset + 0) = (u_current_battery_peak.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current_battery_peak.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current_battery_peak.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current_battery_peak.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->current_battery_peak);
      offset += serializeAvrFloat64(outbuffer + offset, this->total_power_consumed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_hardware_id;
      arrToVar(length_hardware_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_hardware_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_hardware_id-1]=0;
      this->hardware_id = (char *)(inbuffer + offset-1);
      offset += length_hardware_id;
      this->mcu_uptime.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->mcu_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mcu_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->mcu_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->mcu_uptime.sec);
      this->mcu_uptime.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->mcu_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->mcu_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->mcu_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->mcu_uptime.nsec);
      this->connection_uptime.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->connection_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->connection_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->connection_uptime.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->connection_uptime.sec);
      this->connection_uptime.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->connection_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->connection_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->connection_uptime.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->connection_uptime.nsec);
      union {
        float real;
        uint32_t base;
      } u_mcu_temperature;
      u_mcu_temperature.base = 0;
      u_mcu_temperature.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mcu_temperature.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mcu_temperature.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mcu_temperature.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mcu_temperature = u_mcu_temperature.real;
      offset += sizeof(this->mcu_temperature);
      union {
        bool real;
        uint8_t base;
      } u_stop_engaged;
      u_stop_engaged.base = 0;
      u_stop_engaged.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stop_engaged = u_stop_engaged.real;
      offset += sizeof(this->stop_engaged);
      union {
        float real;
        uint32_t base;
      } u_measured_battery;
      u_measured_battery.base = 0;
      u_measured_battery.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_measured_battery.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_measured_battery.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_measured_battery.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->measured_battery = u_measured_battery.real;
      offset += sizeof(this->measured_battery);
      union {
        float real;
        uint32_t base;
      } u_measured_48v;
      u_measured_48v.base = 0;
      u_measured_48v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_measured_48v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_measured_48v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_measured_48v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->measured_48v = u_measured_48v.real;
      offset += sizeof(this->measured_48v);
      union {
        float real;
        uint32_t base;
      } u_measured_24v;
      u_measured_24v.base = 0;
      u_measured_24v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_measured_24v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_measured_24v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_measured_24v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->measured_24v = u_measured_24v.real;
      offset += sizeof(this->measured_24v);
      union {
        float real;
        uint32_t base;
      } u_measured_12v;
      u_measured_12v.base = 0;
      u_measured_12v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_measured_12v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_measured_12v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_measured_12v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->measured_12v = u_measured_12v.real;
      offset += sizeof(this->measured_12v);
      union {
        float real;
        uint32_t base;
      } u_current_battery;
      u_current_battery.base = 0;
      u_current_battery.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_battery.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_battery.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_battery.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_battery = u_current_battery.real;
      offset += sizeof(this->current_battery);
      union {
        float real;
        uint32_t base;
      } u_current_48v;
      u_current_48v.base = 0;
      u_current_48v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_48v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_48v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_48v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_48v = u_current_48v.real;
      offset += sizeof(this->current_48v);
      union {
        float real;
        uint32_t base;
      } u_current_24v;
      u_current_24v.base = 0;
      u_current_24v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_24v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_24v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_24v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_24v = u_current_24v.real;
      offset += sizeof(this->current_24v);
      union {
        float real;
        uint32_t base;
      } u_current_12v;
      u_current_12v.base = 0;
      u_current_12v.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_12v.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_12v.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_12v.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_12v = u_current_12v.real;
      offset += sizeof(this->current_12v);
      union {
        float real;
        uint32_t base;
      } u_current_computer;
      u_current_computer.base = 0;
      u_current_computer.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_computer.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_computer.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_computer.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_computer = u_current_computer.real;
      offset += sizeof(this->current_computer);
      union {
        float real;
        uint32_t base;
      } u_current_battery_peak;
      u_current_battery_peak.base = 0;
      u_current_battery_peak.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current_battery_peak.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current_battery_peak.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current_battery_peak.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->current_battery_peak = u_current_battery_peak.real;
      offset += sizeof(this->current_battery_peak);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->total_power_consumed));
     return offset;
    }

    const char * getType(){ return "warthog_msgs/Status"; };
    const char * getMD5(){ return "0da9e8a166e293e1a5dc327e76c16322"; };

  };

}
#endif
