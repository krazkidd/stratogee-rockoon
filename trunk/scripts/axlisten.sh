#!/bin/bash

# axlisten.sh
# continously grabs data from axlisten and appends it a temp file

# tmp/ is mounted on /. / has 65MB free. If axlisten uses up all this 
# space, the system will crash. If tmp/ had its own filesystem, only 
# those programs that used temporary files might crash. 65 MB is a lot, 
# though. --Mark
axlisten >> /tmp/Packets
