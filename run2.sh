#nice -n 3 ionice -c2 -n7 ./adversarialQueueing -c BB -u Cmdenv -r 0..20
nice -n 3 ionice -c2 -n7 ./adversarialQueueing -c CE3 -u Cmdenv -r 0..20
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c CE7 -u Cmdenv -r 0..20
#nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c varBB -u Cmdenv -r 0..1890
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c varCE71 -u Cmdenv -r 0..1890
#nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c varCE3 -u Cmdenv -r 0..1890
