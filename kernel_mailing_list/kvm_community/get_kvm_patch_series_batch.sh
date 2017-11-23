
#!/bin/bash
cd /root/kde/kernel_mailing_list/kvm_community

for i in `seq 20 31`
do
sh get_kvm_patch_series_today.sh -d 2019-01-${i}
done 

for i in `seq 01 21`
do
sh get_kvm_patch_series_today.sh -d 2019-02-${i}
done 

sh cleanup_json.sh

sh /root/sever-job-notification/send_email.sh "finished: get_kvm_patch_series_batch.sh" "done! please check /root/kde/kernel_mailing_list/kvm_community"


