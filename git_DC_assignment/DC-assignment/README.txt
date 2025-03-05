Implementation of suzuki-kasami algoritm
----------------------------------------

Below are the SW requirements

LANGUAGE: python 3.8 or higher(errors out if executed below Python 3.8 version)
OS: Ubuntu or any flavour of linux

Python packages required
1. mpi4py: MPI for for python provides python bindings for Message Passing Interface(MPI) is a 
standardized and portable message passing system designed to function on a wide varity of
parallel computers

pip3 install mpi4py

2. colorama: Makes ANSI escape character sequences (for producing colored terminal text and cursor positioning

pip3 install colorama

To run the sample
mpiexec -n X python3 suzuki_kasami.py  # where X is the number of processes

ex: mpiexec -n 4 python3 suzuki_kasami.py

To exit: Ctrl-C
