#!bin/bash
bank=$(echo $(( $1 / 32 )))
echo $bank
pin=$(echo $(( $1-($bank*32) )))
echo $pin
