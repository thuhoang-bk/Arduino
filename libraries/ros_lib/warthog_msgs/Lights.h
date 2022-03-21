#ifndef _ROS_warthog_msgs_Lights_h
#define _ROS_warthog_msgs_Lights_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "warthog_msgs/RGB.h"

namespace warthog_msgs
{

  class Lights : public ros::Msg
  {
    public:
      warthog_msgs::RGB lights[4];
      enum { LIGHTS_FRONT_LEFT = 0 };
      enum { LIGHTS_FRONT_RIGHT = 1 };
      enum { LIGHTS_REAR_LEFT = 2 };
      enum { LIGHTS_REAR_RIGHT = 3 };

    Lights():
      lights()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->lights[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      offset += this->lights[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "warthog_msgs/Lights"; };
    const char * getMD5(){ return "6a0a6d0144b1184a10c871c946ce5c3d"; };

  };

}
#endif
