# dhcp-server-config
This project helps you to configure your dhcp server by adding arguments to dhcpd.conf file.

# build and debug

Use Makefile to build and debug the program.

# usage
sudo ./theconfig ip-dhcp-pool poolname

sudo ./theconfig poolname option arg1 arg2

# options
-reset          :erase the dhcpd.conf and config_info.txt files


exit            :exit the program with no change in files


network         :add 2 arguments after this option to ser subnet and netmask


default-router  :add gateway as an argument after this option


dns-server      :add dns as an argument after this option 

# notes
 -Do not forget to run the program by sudo access.

-this program accept just one dns address.
