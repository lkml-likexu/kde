#!/bin/bash
# why 48? you need define the max value of your subscriptions,
# the default value is 30 entries per page
for i in `seq 1 1 48`
do
curl https://api.github.com/user/subscriptions?page=$i \
 -H "Accept: application/vnd.github.beta+json" \
-u xuliker:$username@$password >> my_subscriptions.txt
done