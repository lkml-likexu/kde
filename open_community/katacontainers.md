#### 1. Setup Kata 

* 16 Jan 2018 :  https://github.com/kata-containers/documentation/wiki/Developer-Guide

  * specifically for developers	

  * https://docs.docker.com/install/linux/docker-ce/ubuntu/

```
"hypervisor-container-runtime"
COMMANDS:
     delete      Delete any resources held by one or more containers
     exec        Execute new process inside the container
     kill        Kill sends signals to the container's init process
     list        lists containers started by kata-runtime with the given root
     pause       suspend all processes in a container
     ps          ps displays the processes running inside a container
     resume      unpause all previously paused processes in a container
     run         create and run a container
     start       executes the user defined process in a created container
     state       output the state of a container
     version     display version details
     kata-check  tests if system can run Kata Containers
     kata-env    display settings
     help, h     Shows a list of commands or help for one command




# centos operation https://docs.docker.com/install/linux/docker-ce/centos/#set-up-the-repository
apt-get remove docker-ce docker docker-engine docker.io
apt-get update
apt-get install -y apt-transport-https ca-certificates curl software-properties-common make gcc
export ALL_PROXY='socks5://child-prc.intel.com:913'
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | apt-key add -
apt-key fingerprint 0EBFCD88
add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
apt-get update

lsmod|grep over
modinfo overlay
modprobe overlay

lsmod|grep btrfs
modinfo btrfs
modprobe btrfs

apt-get install docker-ce -y
apt-cache madison docker-ce
# apt-get install docker-ce=<VERSION>
docker run hello-world

mkdir -p /etc/systemd/system/docker.service.d
vim /etc/systemd/system/docker.service.d/http-proxy.conf
# [Service]
# Environment="HTTP_PROXY=http://child-prc.intel.com:913/"
systemctl daemon-reload
# 修改Docker的systemd文件，添加http代理配置。
# 修改/lib/systemd/system/docker.service
# EnvironmentFile=-/etc/sysconfig/docker
# 创建或修改/etc/sysconfig/docker
# HTTP_PROXY=http://proxy.example.com:80/
# HTTPS_PROXY=http://proxy.example.com:80/
# NO_PROXY=localhost,127.0.0.1,internal-docker-registry.somecorporation.com
# export HTTP_PROXY HTTPS_PROXY NO_PROXY
# 刷新配置,使代理生效
# systemctl daemon-reload
# systemctl restart docker

# 使用自定义的kernel可以使用如下脚本来验证config配置
# https://raw.githubusercontent.com/moby/moby/master/contrib/check-config.sh
```

* install golang

```
wget https://dl.google.com/go/go1.10.linux-amd64.tar.gz
tar -C /usr/local -xzf go1.10.linux-amd64.tar.gz
export PATH=$PATH:/usr/local/go/bin
```

* [Installing Clear Containers 3.0 on Ubuntu](https://github.com/clearcontainers/runtime/blob/master/docs/ubuntu-installation-guide.md)
  * You will installed the Clear Containers linux-container 
    * cc-ksm-throttler 
    * cc-proxy 
    * cc-runtime 
      * cc-runtime-bin 
      * cc-runtime-config 
      * cc-shim 
    * clear-containers-image 
    * linux-container 
    * qemu-lite

```
cc-proxy cc-runtime cc-shim clear-containers-image linux-container                                              

sh -c "echo 'deb http://download.opensuse.org/repositories/home:/clearcontainers:/clear-containers-3/xUbuntu_$(lsb_release -rs)/ /' >> /etc/apt/sources.list.d/clear-containers.list"

export http_proxy=http://child-prc.intel.com:913
export https_proxy=https://child-prc.intel.com:913
export ftp_proxy=http://child-prc.intel.com:913

export http_proxy=http://10.239.4.80:913
export https_proxy=https://10.239.4.80:913
export ftp_proxy=http://10.239.4.80:913
export PATH=$PATH:$(go env GOPATH)/bin
export GOPATH=$(go env GOPATH)

wget -qO - http://download.opensuse.org/repositories/home:/clearcontainers:/clear-containers-3/xUbuntu_$(lsb_release -rs)/Release.key | sudo apt-key add -

apt-get update
apt-get -y install cc-runtime cc-proxy cc-shim  # verrrrry slow

mkdir -p /etc/systemd/system/docker.service.d/
cat <<EOF | tee /etc/systemd/system/docker.service.d/clear-containers.conf
[Service]
ExecStart=
ExecStart=/usr/bin/dockerd -D --add-runtime cc-runtime=/usr/bin/cc-runtime --default-runtime=cc-runtime
EOF

systemctl daemon-reload
systemctl enable docker.service
systemctl restart docker

apt-get install uml-utilities -y
modprobe tun

docker run -ti busybox sh
# TODO docker: Error response from daemon: OCI runtime create failed: Could not create TAP interface: LinkAdd() failed for macvtap name tap0: operation not supported: unknown. 
# CONFIG_MACVLAN=y
# CONFIG_MACVTAP is not set
```

* Build and install a Kata Containers runtime

```
export PATH=$PATH:$(go env GOPATH)/bin
export GOPATH=$(go env GOPATH)

go get -d -u github.com/kata-containers/runtime
cd $GOPATH/src/github.com/kata-containers/runtime

# Set to either 'cc' or 'runv'.
runtime=

make KATA_RUNTIME=$runtime && sudo -E PATH=$PATH make KATA_RUNTIME=$runtime install

ls /usr/local/bin/kata-runtime
kata-runtime kata-check  # Check hardware requirements

# WARN[0000] kernel module parameter has unexpected value  description="Intel KVM" expected=Y name=kvm_intel parameter=nested source=runtime type=module value=N
# cat /sys/module/kvm_intel/parameters/nested
rmmod kvm_intel;modprobe kvm-intel nested=1

# Enable full debug
sed -i -e 's/^# *\(enable_debug\).*=.*$/\1 = true/g' /usr/share/defaults/kata-containers/configuration.toml
```

* Build Kata-containers

```
go get -d -u github.com/kata-containers/proxy
cd $GOPATH/src/github.com/kata-containers/proxy && make && make install
 
go get -d -u github.com/kata-containers/shim
cd $GOPATH/src/github.com/kata-containers/shim && make && sudo make install

# Create an image
go get -d -u github.com/kata-containers/agent
cd $GOPATH/src/github.com/kata-containers/agent && make

go get -d -u github.com/kata-containers/osbuilder

cd $GOPATH/src/github.com/kata-containers/osbuilder/rootfs-builder
# modify clearlinux/Dockerfile.in
# echo "proxy=http://10.239.4.80:913" >> /etc/dnf/dnf.conf
# echo "baseurl=http://mirrors.163.com/fedora/releases/27/Everything/x86_64/os/" >> /etc/dnf/dnf.conf
# echo "fastestmirror=1" >> /etc/dnf/dnf.conf
# dnf install -y git systemd pkgconfig gcc
script -fec 'sudo -E GOPATH=$GOPATH USE_DOCKER=true ./rootfs.sh clearlinux'

docker info|grep -i "default runtime"|cut -d: -f2-|grep -q runc  && echo "SUCCESS" || echo "ERROR: Wrong default runtime"
# modify default_run-time=runc /etc/systemd/system/docker.service.d/clear-containers.conf

# vi /etc/hosts
# 10.239.4.80     child-prc.intel.com
# echo "10.239.4.80     child-prc.intel.com" >> /etc/hosts
# echo "proxy=http://10.239.4.80:913" >> /etc/dnf/dnf.conf

cd $GOPATH/src/github.com/kata-containers/osbuilder/image-builder
mkdir ../rootfs-builder/rootfs
script -fec 'sudo -E USE_DOCKER=true ./image_builder.sh ../rootfs-builder/rootfs'


cat <<EOF | tee /etc/yum.repos.d/fedora-ustc.repo
[fedora] 
name=Fedora $releasever - $basearch - ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/releases/$releasever/Everything/$basearch/os/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=fedora-$releasever&arch=$basearch 
enabled=1 
metadata_expire=7d 
gpgcheck=1 
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch 
 
[fedora-debuginfo] 
name=Fedora $releasever - $basearch - Debug - ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/releases/$releasever/Everything/$basearch/debug/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=fedora-debug-$releasever&arch=$basearch 
enabled=0 
metadata_expire=7d 
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch 
 
[fedora-source] 
name=Fedora $releasever - Source - ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/releases/$releasever/Everything/source/SRPMS/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=fedora-source-$releasever&arch=$basearch 
enabled=0 
metadata_expire=7d 
gpgcheck=1 
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch 
EOF


cat <<EOF | tee /etc/yum.repos.d/fedora-updates-ustc.repo
[updates]
name=Fedora $releasever - $basearch - Updates - ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/updates/$releasever/$basearch/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=updates-released-f$releasever&arch=$basearch 
enabled=1 
gpgcheck=1 
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch 
 
[updates-debuginfo] 
name=Fedora $releasever - $basearch - Updates - Debug -ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/updates/$releasever/$basearch/debug/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=updates-released-debug-f$releasever&arch=$basearch 
enabled=0 
gpgcheck=1 
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch 
 
[updates-source] 
name=Fedora $releasever - Updates Source - ustc
failovermethod=priority 
baseurl=http://mirrors.ustc.edu.cn/fedora/updates/$releasever/SRPMS/ 
#mirrorlist=https://mirrors.fedoraproject.org/metalink?repo=updates-released-source-f$releasever&arch=$basearch 
enabled=0 
gpgcheck=1 
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-$basearch
EOF

yum makecache


dnf remove fedora-release-27 -y



rm -rf /etc/yum.repos.d/*.repo
cat > /etc/yum.repos.d/clear-linux.repo << EOF
[main]
cachedir=/var/cache/dnf-clear
keepcache=0
debuglevel=2
logfile=/var/log/dnf.log
exactarch=1
obsoletes=1
gpgcheck=0
plugins=0
installonly_limit=3
reposdir=/root/mash

[clear]
name=Clear
failovermethod=priority
baseurl=https://download.clearlinux.org/current/x86_64/os/
enabled=1
gpgcheck=0
EOF

yum makecache

echo "proxy=http://10.239.4.80:913" >> /etc/yum.conf

cat > /etc/yum.repos.d/CentOS7-Base-163.repo << EOF
# CentOS-Base.repo
#
# The mirror system uses the connecting IP address of the client and the
# update status of each mirror to pick mirrors that are updated to and
# geographically close to the client.  You should use this for CentOS updates
# unless you are manually picking other mirrors.
#
# If the mirrorlist= does not work for you, as a fall back you can try the 
# remarked out baseurl= line instead.
#
#
[base]
name=CentOS-$releasever - Base - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os
baseurl=http://mirrors.163.com/centos/$releasever/os/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#released updates
[updates]
name=CentOS-$releasever - Updates - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=updates
baseurl=http://mirrors.163.com/centos/$releasever/updates/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#additional packages that may be useful
[extras]
name=CentOS-$releasever - Extras - 163.com
#mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=extras
baseurl=http://mirrors.163.com/centos/$releasever/extras/$basearch/
gpgcheck=1
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7

#additional packages that extend functionality of existing packages
[centosplus]
name=CentOS-$releasever - Plus - 163.com
baseurl=http://mirrors.163.com/centos/$releasever/centosplus/$basearch/
gpgcheck=1
enabled=0
gpgkey=http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-7
EOF
```

* https://github.com/kata-containers/documentation/wiki/Developer-Guide#checking-docker-default-runtime

#### 2. Runtimes 

* https://github.com/kata-containers/runtime
  * if one runtime is a better suited starting point than the other
  * So for now Kata **supports both** cc-runtime and runV,
    * because we wanted the Kata community to be able to **run the entire stack** (with either one of the two runtimes) 
* will **merge** those two runtimes into a single one
  * https://github.com/kata-containers/runtime/issues/31
    * Eventually Clear Containers will be **deprecated** in favor of Kata Containers
    * start once we reach the 1.0 Kata Containers release.

#### 3. Secure isolation

1. **Define** the specific **problems** we are trying to address with secure isolation.
2. Develop **common terminology & understanding** of the problem & solution space.
3. Capture all the requirements, considerations, notes, resources, and discussions around Kubernetes secure isolation in single place to **defrag** isolation discussions.
4. Provide a structure for evaluating **potential solutions**.
5. This is ***not* a solution proposal,** but I am hoping that it will provide a smooth path for follow up discussions and lead to a widely accepted solution.
* https://docs.google.com/document/d/1QQ5u1RBDLXWvC8K3pscTtTRThsOeBSts_imYEoRyw8A/edit#heading=h.ypyhxoaw8f95

#### 4. Contributors 

```
is:open is:pr archived:false user:kata-containers
```

* https://github.com/kata-containers/community/blob/master/CONTRIBUTING.md
* feel free to drop in on irc / Slack
  * https://github.com/kata-containers/community/blob/master/CONTRIBUTING.md#contact
* the developer guide
  * https://github.com/kata-containers/documentation/wiki/Developer-Guide
* the new "Table of Contents" document 
  * https://github.com/kata-containers/kata-containers/blob/master/README.md

#### 5. Meetings

* the Architecture Committee meeting 
  * how to go about creating the Kata Containers runtime (February 12, 16:00UTC (Feb 12, 8am Pacific))
    * Samuel and Xu will give an overview of both the Clear Containers and runV runtimes
    * **Deploying kata containers via k8s daemonset into crio** would be very nice.
  * https://etherpad.openstack.org/p/katacontainers-2018-architecture-committee-mtgs
* the Working Committee meeting
  * the idea of a weekly or bi-weekly **status blog** came up  (Cameron Seader cseader@suse.com)
    * The Kata homepage will have a blog page up in the next two weeks or less, which is where these posts would live
      * PR selection :: any significant / interesting PRs
      * pick one part of the system and explain what it is, how it works, etc. A few examples:
        - What is the kata-agent / kata-proxy / kata-shim?
        - What is osbuilder?
        - How does docker use the runtime?
        - How is the overall system tested (static analysis, unit-tests, CI, metrics, etc)?
        - How is documentation written+reviewed?
        - How does the project use pullapprove?
      * What are all those repositories for? (answer in the form of a very basic "table of contents":
        https://github.com/kata-containers/kata-containers/blob/master/README.md :)
      * How to contribute to the project
      * New features
      * plans for the future
      * upcoming events showcasing Kata Containers



* the k8s sig-node community meeting 
  * The presentation by Xu and Samuel (13 Feb 2018)
    * https://docs.google.com/presentation/d/17J_HDKDddae0kaxAx6SooVbhXpMrmhhD190P6FHC_p4/edit#slide=id.p

#### 5. CI testing

- we do in these Jenkins jobs is to setup the Kata Containers environment with latest changes in 
  - an **Ubuntu 16.04 VM instance at Azure** and execute the docker integration tests. 
- All the CI scripts are located in the https://github.com/kata-containers/tests repository.
- some random failures
  - opened https://github.com/kata-containers/runtime/issues/35 and after fixing this, we should have an stable CI
- Next steps:
  - Add jobs for the rest of the Kata Containers Components. 
  - Add kata-containers-runv runtime in the tests.
  - Add other distros in addition to Ubuntu 16.04. 
  - Add CRI-O, k8s and Openshift tests

#### 6. Arch Related 

* AMD Secure Encrypted Virtualization 
  * **Per container/VM memory encryption** is an exciting feature 社区存在大量讨论

#### 7. Milestones

* Fri, **26 Jan** 2018 21:45:51 +0100 
  * we can **run our first Docker containers** with Kata


```
root@xulike-station:~/go/src/github.com/kata-containers/runtime# kata-runtime kata-check
INFO[0000] CPU property found                            description="Intel Architecture CPU" name=GenuineIntel source=runtime type=attribute
INFO[0000] CPU property found                            description="Virtualization support" name=vmx source=runtime type=flag
INFO[0000] CPU property found                            description="64Bit CPU" name=lm source=runtime type=flag
INFO[0000] CPU property found                            description=SSE4.1 name=sse4_1 source=runtime type=flag
INFO[0000] kernel property found                         description="Kernel-based Virtual Machine" name=kvm source=runtime type=module
INFO[0000] kernel property found                         description="Host kernel accelerator for virtio" name=vhost source=runtime type=module
INFO[0000] kernel property found                         description="Host kernel accelerator for virtio network" name=vhost_net source=runtime type=module
INFO[0000] kernel property found                         description="Intel KVM" name=kvm_intel source=runtime type=module
INFO[0000] Kernel property value correct                 description="Intel KVM" name=kvm_intel parameter=nested source=runtime type=module value=Y
INFO[0000] Kernel property value correct                 description="Intel KVM" name=kvm_intel parameter=unrestricted_guest source=runtime type=module value=Y
INFO[0000] System is capable of running Kata Containers  source=runtime
INFO[0000] device available                              check-type=full device=/dev/kvm source=runtime
INFO[0000] feature available                             check-type=full feature=create-vm source=runtime
INFO[0000] System can currently create Kata Containers   source=runtime
```

* Mon, 29 Jan 2018 Let me try it **inside Dell**
  * Dell Innovation House, Cherrywood Science & Technology Park, Cabinteely, Dublin 18, Ireland
* 16 Feb 2018 
  * enabled the Jenkins instance :: http://kata-jenkins-ci.westus2.cloudapp.azure.com/


```
/usr/bin/qemu-lite-system-x86_64 -name pod-c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145 -uuid 9d0e04b0-8974-4244-9dac-162fe6e8d670 -machine pc,accel=kvm,kernel_irqchip,nvdimm -cpu host -qmp unix:/run/virtcontainers/pods/c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145/mon-9d0e04b0-8974,server,nowait -qmp unix:/run/virtcontainers/pods/c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145/ctl-9d0e04b0-8974,server,nowait -m 2048M,slots=2,maxmem=8950M -device virtio-serial-pci,id=serial0 -device virtconsole,chardev=charconsole0,id=console0 -chardev socket,id=charconsole0,path=/run/virtcontainers/pods/c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145/console.sock,server,nowait -device nvdimm,id=nv0,memdev=mem0 -object memory-backend-file,id=mem0,mem-path=/usr/share/kata-containers/kata-containers-2018-02-28-03:35:35.408886441+0800-ec738d4,size=134217728 -device virtio-scsi-pci,id=scsi0 -device virtserialport,chardev=charch0,id=channel0,name=agent.channel.0 -chardev socket,id=charch0,path=/run/virtcontainers/pods/c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145/kata.sock,server,nowait -device virtio-9p-pci,fsdev=extra-9p-kataShared,mount_tag=kataShared -fsdev local,id=extra-9p-kataShared,path=/run/kata-containers/shared/pods/c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145,security_model=none -netdev tap,id=network-0,vhost=on,vhostfds=3:4:5:6:7:8:9:10,fds=11:12:13:14:15:16:17:18 -device driver=virtio-net-pci,netdev=network-0,mac=02:42:ac:11:00:02,mq=on,vectors=18 -rtc base=utc,driftfix=slew -global kvm-pit.lost_tick_policy=discard -vga none -no-user-config -nodefaults -nographic -daemonize -kernel /usr/share/clear-containers/vmlinuz-4.9.60-84.container -append root=/dev/pmem0p1 rootflags=dax,data=ordered,errors=remount-ro rw rootfstypcde=ext4 tsc=reliable no_timer_check rcupdate.rcu_expedited=1 i8042.direct=1 i8042.dumbkbd=1 i8042.nopnp=1 i8042.noaux=1 noreplace-smp reboot=k console=hvc0 console=hvc1 iommu=off cryptomgr.notests net.ifnames=0 pci=lastbus=0 debug systemd.show_status=true systemd.log_level=debug panic=1 initcall_debug init=/usr/lib/systemd/systemd systemd.unit=kata-containers.target systemd.mask=systemd-networkd.service systemd.mask=systemd-networkd.socket ip=::::::c0ed11a17612ce0d7d6d67f852a3aa3448e3ca2e788ff0dc1d19a238833b8145::off:: agent.log=debug -smp 1,cores=1,threads=1,sockets=1,maxcpus=240
```

