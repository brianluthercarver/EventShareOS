# EventShareOS Network and Serial Protocol
One of the basic tenets behind EventShareOS is test injection by a remote source. Network and serial communications are an excellent means to monitor, communicate, and sending commands. This protocol is shared between network and serial communications.

## Design Philosophy  
This protocol is designed to support test injection, data transfers, and application data. Each command will have it's own version number allowing forward and backwards compatibility. 

## Basic Structure
The basic unit of the serial protocol is a byte. The protocol is byte order specific.  The data field is a variable length field limited by a 16 bit number minus 5 bytes.  All bytes are listed as Most Significant Byte order (MSB).


| Offset | Count  | Name | Description |
|--------|--------|------|-------------|
| 0 | 1 | Version | Version number of each command |
| 1 | 1 | Command | Command byte for processing. |
| 2 | 2 | Length  | Total Length including two bytes CRC |
| 4 | N | Data    | n bytes of data limited by 16 bit number |
| N+5 | 2 | CRC | 16 bit CRC, unknown algorithm  |

## Commands
The command byte is a descriptor of the data field. The command byte is reserved and shall not be modified by any application. Having said that there will be a provision for an application specific command for application data. 

Each command will have a specific number listed in hex (decimal) followed a table describing the fields with in the data field. The offset is set to zero at the beginning of the data.

### Event Command 0x01 (1)
The event command is just the (E,V) pair used within the EventShareOS.  

| Offset | Count  | Name | Description |
|--------|--------|------|-------------|
| 0 | 4 | Event | Unsigned 32 bit integer representing the event number|
| 4 | 4 | Value | Unsigned 32 bit integer representing the value|

### Performance Data 0x02 (2)
Performance data is a variable multi-byte description of the systems performance.

| Offset | Count  | Name | Description |
|--------|--------|------|-------------|
| 0 | 1 | Modules | The number of modules |
| 1 | 4 | System  | Avg system overhead in milliseconds |
| 4 | 4 | Queue Miss | Count of event queue misses |
| 9 | 4 | Data Queue Miss | Count of any data queue misses |
| 13 | 4 | Module one | Module avg time in milliseconds |
| 17 | X | Next Module | ... repeat modules as per field 1 |

### Application Data 0x03 (3)
Application data is encapsulated data placed in the data field. 

| Offset | Count  | Name | Description |
|--------|--------|------|-------------|
| 0 | 2 | Assignment | Number assigned for application data type |
| 3 | 2 | Length | The number of bytes following |
| 5 | N | App Data | The encapsulated data |



[Back to Readme](../README.adoc)

> **Copyright** <p> EventShareOS is Copyright (c) by Brian L Carver 2026 under a MIT license. See the file: EventShareOS_License.txt for more details. 

[License](../EventShareOS_License.txt)