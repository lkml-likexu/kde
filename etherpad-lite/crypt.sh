#!/bin/bash

# yum install gnupg
# gpg --full-generate-key
# gpg --gen-revoke "Like Xu (for-sync) <xuliker@zju.edu.cn>"
# gpg --list-keys
# gpg --delete-key "user ID"
# gpg --armor --output public-key.txt --export "user ID"
# gpg --armor --output private-key.txt --export-secret-keys
# gpg --import key.txt
# gpg --sign demo.txt
# gpg --clearsign demo.txt
# gpg --detach-sign demo.txt
# gpg --armor --detach-sign demo.txt
# gpg --local-user "sender id" --recipient "receiver id" --armor --sign --encrypt demo.txt
# gpg --verify demo.txt.asc demo.txt
# /Users/username/.gnupg/
# gpg --delete-secret-keys "Like Xu (for-sync) <xuliker@zju.edu.cn>"
# gpg --import private-key.txt

cd $HUB/kde/etherpad-lite

mv $HUB/etherpad-lite/var/dirty.db dirty.db
gpg --recipient "Like Xu (for-sync) <xuliker@zju.edu.cn>" --output dirty.db.encrypt --encrypt dirty.db
rm dirty.db

gpg --decrypt dirty.db.encrypt > dirty.db
rm dirty.db.encrypt
mv dirty.db $HUB/etherpad-lite/var/
sudo chown aaron:aaron $HUB/etherpad-lite/var/dirty.db

# work on linux
kill -9 `ps -ef | grep "therpad" | grep "node" | awk '{ print $2 }'`
gpg --recipient "Like Xu (for-sync) <xuliker@zju.edu.cn>" --output /media/aaron/MAGIC/dirty.db.encrypt --encrypt $HUB/etherpad-lite/var/dirty.db
rm $HUB/etherpad-lite/var/dirty.db

gpg --decrypt /media/aaron/MAGIC/dirty.db.encrypt > $HUB/etherpad-lite/var/dirty.db
rm /media/aaron/MAGIC/dirty.db.encrypt
sudo chown aaron:aaron $HUB/etherpad-lite/var/dirty.db
etherpad

# 加密自身
gpg --recipient "Like Xu (for-sync) <xuliker@zju.edu.cn>" --output crypt.sh.encrypt --encrypt crypt.sh
gpg --decrypt crypt.sh.encrypt > crypt.sh