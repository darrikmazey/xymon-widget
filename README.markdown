
# Xymon-Widget

Xymon-Widget is a desktop widget for the Nokia N900 (or any maemo device) that polls a xymon server and reports status via icon color and notification messages.

## Author

Darrik Mazey (darrik@darmasoft.com)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)

## Repository

Add the following to /etc/apt/sources.list or /etc/apt/sources.list.d/hildon-application-manager.list

	deb http://apt.darmasoft.net fremantle-1.2 free

Or use the following settings in the application manager:

	* Catalog Name: darmasoft
	* Web address: http://apt.darmasoft.net
	* Distribution: fremantle-1.2
	* Components: free

## Configuration

In the settings, Server Address can be a hostname (e.g. xymon.darmasoft.com) or a hostname with protocol (e.g. https://xymon.darmasoft.com).  SSL functions, but invalid certificates are ignored without warning.

## Current Version

* 0.28

## Links

* [Xymon](http://www.xymon.com/)
* [Qt](http://qt.nokia.com/products/)
