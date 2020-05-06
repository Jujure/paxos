# Paxos made moderately working in C++

## Why does this exists ?
This repository is a modest implementation of paxos, a distributed system algorithm described in [The part time parliament](https://lamport.azurewebsites.net/pubs/lamport-paxos.pdf).

It was realised for pedagogical purposes, this implementation is nowhere neer optimized or even usable in any way.

It is simply a support to understand the main ideas of the algorithm with (I hope) pertinent logging and some basic interraction.

This was realised as part of a school assignment but I wanted to do this since a while so the assignment was the perfect occasion to implement this.
The specifications of the assignment were basically "Write an article about any network related subject to go further that we have seen in class" I came up with the terrible idea of proposing an implementation along with the article (available in the repository) which further details the implementation and the algorithm, hope you will enjoy.

**Do not use this implementation in a real project**

## How can I use this ?

### Install
To compile the binary into the repository
```shell=zsh
./autogen.sh
./configure
make
```

### Special Requirements
```
boost
autoconf-archive
A C++ compiler I guess
```

### Launch

You must then launch the binary by putting a configuration file in argument and a server name
```shell=zsh
./paxos {config} {name}
```

### Configuration

You can find multiple configuration files in the repository already done for you, they are pretty straight forward to understand.

Let's say you want to distribute your system on 2 server, you have to launch 2 instances of the binary each with the same configuration file but each with a distinct name. The configuration file contains informations on all the servers composing the system.
The second argument you are giving in the command line is the name of the server that THIS instance represents.
The server with a name equal to the one in the command line, will have its specified ip and port binded for listening, the others are simply the other servers composing your system (which also binded their corresponding ip/port in their respective instances).


### Use

Once you started (or not :eyes:) your instances, you can send a SIGTSTP (with a ctrl+z for example) to an instance and it will try to initiate a ballot to synchronize with other servers.


## What does it do ?

The goal is to synchronize a decree between all the servers.

In our case, a decree is simply an int, we want every every server to have the same.

Servers keep their data on disk in simple files (the goal is to keep it simple we will not go with big databases)

Each server create a directory with the name given in the configuration, this directory will contain multiple files, most of them are only here to keep track of the execution of the algorithm.

The one that will be really interesting is the `decree.txt` file. It contains a single decree (an int) which is the decree this server currently holds.

The goal of the algorithm is that this file will eventually be identical between every server regardless of crashes, network interruption or anything.

An other key part is that whenever the servers agreed on a decree to share, it doesn't matter how many ballots you initiate on any server, the decree will always be the same.

You can try this by launching only 3 of the 4 servers (which simulated the fact that the 4th has crashed), initiating a ballot, see that the three agreed but the 4th is not aware of that decree (because it was down), and then start the 4th, and initiate a ballot in any server to see that the 4th actually agreed with the previous decree and registered it in its personnal data.
