//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "VariableDelayChannel.h"

VariableDelayChannel::VariableDelayChannel()
    :cDatarateChannel()
{
    // TODO Auto-generated constructor stub
}

VariableDelayChannel::~VariableDelayChannel()
{
    // TODO Auto-generated destructor stub
}


void VariableDelayChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    SimTime *delaymean, *delaystd = new SimTime();
    delaymean->parse("1ms");
    delaystd->parse("500us");
    cDatarateChannel::setDelay(uniform((*delaymean).dbl(),(*delaystd).dbl()));
    cDatarateChannel::processMessage(msg, t, result);
}
