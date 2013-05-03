nice -n 3 ionice -c2 -n7 ./adversarialQueueing -c cdBB -u Cmdenv -r 0..3149
nice -n 3 ionice -c2 -n7 ./adversarialQueueing -c cdCE3 -u Cmdenv -r 0..1700
nice -n 3 ionice -c2 -n7 ./adversarialQueueing -c cdCE3 -u Cmdenv -r 1701..3149
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c cdCE71 -u Cmdenv -r 0..900
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c cdCE71 -u Cmdenv -r 901..1700
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c cdCE71 -u Cmdenv -r 1701..2400
nice -n 3 ionice -c2 -n7  ./adversarialQueueing -c cdCE71 -u Cmdenv -r 2401..3149


