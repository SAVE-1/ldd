# Setting up remote SSH visual studio code, Ubuntu

Primary:
- Setup the primary machine to accept SSH connections using password.
	- Edit a file and restart a few services
- Set a password for the user - ubuntu

Windows
- Connect VSCode to Primary over SSH
	- Install an extension on VSCode


```

multipass networks
multipass launch --network <my network> --name primary

sudo passwd ubuntu

sudo vim /etc/ssh/sshd_config

KbdInteractiveAuthentication no -> KbdInteractiveAuthentication yes

sudo systemctl daemon-reload
sudo service ssh restart

sudo passwd ubuntu

# install utilities
sudo apt update
sudo apt upgrade
sudo apt install -y build-essential linux-headers-$(uname -r) kmod

# connection in VSCode
install: Remote Development -extension (VSCode)
ubuntu@<ip>

```


