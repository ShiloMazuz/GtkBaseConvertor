
# BasedIP  

A Gtk IP address converter written in C++




## Installation 

First make sure you have the Gtk Development packages installed

```bash
sudo apt install libgtkmm-3.0-dev
```
To deploy this project run 

```bash
make
```
followed by 
```bash
make install
```


## Roadmap

- Calculating values using things other than just an ip address
    
    -  subnet mask to prefix
    - hosts to subnet mask/ prefix
    - binary ip to decimal ip
    - ip + mask to network range
- possible support for IPv6 
