#include "vpd3canframeparser.h"

VPD3CANFrameParser::VPD3CANFrameParser()
{

}

QVector<Measurement> VPD3CANFrameParser::parse(const QCanBusFrame& frame){
    QVector<Measurement> m;
    if (frame.frameType() != QCanBusFrame::ErrorFrame){
        if (vm_.parseCANFrame(frame)){
            if (vm_.isComplete()){
                if (!vm_.hasErrorResponse()){
                    m = parseVolvoMessage(vm_);
                    vm_.clear();
                }
            }
        }
    }
    return m;
}

void VPD3CANFrameParser::setSubject(const QString& s){
    subject_ = s;
}

QVector<Measurement> VPD3CANFrameParser::parseVolvoMessage(const VolvoMessage& vm){
    //qDebug() << "VPD3CANFrameParser:" << vm.toString();

    QByteArray data = vm.getData();
    QVector<Measurement> measurements;

    switch (vm.getCANId()){
        case 0x0042401E:
            //qDebug() << "0x0042401E" << (((quint8)data[6]) << 8) + (quint8)data[7];
              measurements.push_back(Measurement(
                                subject_,
                                "Engine Speed",
                                (((quint8)data[6]) << 8) + (quint8)data[7],
                                0,
                                "RPM"
                         ));
              measurements.push_back(Measurement(
                subject_, "Rail Pressure", (((quint8)data[3]) << 8) + (quint8)data[4], 0, "bar"
              ));

           break;
        case 0x02800006:
            break;

    case 0x01400002:
            break;

        case 0x000FFFFE:
            switch (vm.getCommandId()) {
                case 0xA6:
                    switch ((vm.getFunctionId() << 8) + vm.getFunctionParam()){
                        /*case 0x0004:
                            printf ("Coolant temp binary: %i \n", ((data_[0] << 8) + data_[1]));
                            break;

                        case 0x0005:
                            printf ("Coolant temp unknown scale: %i \n", ((data[0] << 8) + data[1]));
                            break;*/

                        case 0x000B:
                            measurements.push_back(Measurement(
                              subject_, "Boost Pressure", (((quint8)data[0]) << 8) + (quint8)data[1], 0, "mbar"
                            ));
                            break;

                        case 0x000F:
                        case 0x0F01:
                        case 0x0F48:
                            printf ("Manifold air temp: %f \n", ((data[0] << 8) + data[1])/10.0 );
                            break;

                    /*
                        case 0x0011:
                            printf ("Unknown throttle related: %x %x %x\n", data[0], data[1], data[2]);
                            break;

                        case 0x0023:
                            printf ("Rail pressure 0x0023: %.2f bar\n", ((data[0] << 8) + data[1])/10.0);
                            break;*/

                        case 0x0061:
                            printf ("ECU temperature: %.2f C\n", ((data[0] << 8) + data[1])/100.0);
                            break;
        /*
                        case 0x0101:
                        case 0x0102:
                        case 0x0103:
                        case 0x0104:
                        case 0x0105:
                        case 0x0106:
                        case 0x0107:
                        case 0x0108:
                        case 0x0109:
                        case 0x010A:
                        case 0x010B:
                        case 0x010C:
                        case 0x010D:
                        case 0x010E:
                            printf("Reported supported requests.\n");
                            for (unsigned int i=1;i<vm.actual_length; i+=2){
                                printf("%02X %02X\n", data[i], data[i+1]);
                                add_supported_request(data[i], data[i+1]);
                            }
                            print_supported_requests();
                            break;


                        case 0xE020: //Related to intake air temp. stable at 0x2BC and 0x3EE
                            break;

                        case 0x3004:
                            printf ("Boost pressure binary: %i\n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x300E:
                            printf ("Boost temp binary: %i\n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x0F00:
                            printf ("Coolant temp unknown scale2: %i \n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x0F2E:
                        case 0x0F31:
                        case 0x0F32:
                            printf ("Coolant temp unknown scale3: %i \n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x0F8A:
                            printf ("Coolant temp unknown scale4: %i \n", ((data[0] << 8) + data[1]));
                            break;
                            // 0x0F8B?
                        case 0x0F8C:
                        case 0x0F8E:
                        case 0x1F5C:
                        case 0xDC86:
                            printf ("Coolant temp unknown scale5: %i \n", ((data[0] << 8) + data[1]));
                            break;
        */
                        case 0x0F35:
                            printf ("Throttle: %.2f%%\n", ((float)((data[0] << 8) + data[1]))/10.230);
                            break;

                        case 0x0F63:
                            printf ("Atmospheric preassure: %.2f mbar\n", ((double)((data[0] << 8) + data[1])));
                            break;

                        case 0x0F65:
                            printf ("Battery voltage: %.2fV\n", ((double)((data[0] << 8) + data[1]))/42.0);
                            break;


                        case 0x0F70:
                            if (data[1] & 0x04) { //probably a bitfield of flags
                                printf ("Water in fuel\n");
                            } else {
                                printf ("No water in fuel\n");
                            }
                            break;

                         case 0x1F5D:
                         case 0x1F5F:
                            {
                                uint rail_pressure = ((data[0] << 8) + data[1]);
                                if (rail_pressure != 3550){
                                    printf ("Rail pressure: (0x1F5F) %.2f bar\n", rail_pressure/10.0);

                                    } else {
                                    printf ("Rail pressure over or under limits.\n");
                                }
                            }
                            break;

                        /*case 0x0FFC:
                            {
                                uint rail_pressure = ((data[0] << 8) + data[1]);
                                if (rail_pressure != 0){
                                    printf ("Rail pressure (0x0FFC): %.2f bar\n", rail_pressure/10.0);

                                } else {
                                    printf ("Rail pressure over or under limits.\n");
                                }
                            }

                            break;*/

                        /*
                        case 0x2152:
                            printf("Status bitfield:  "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",  BYTE_TO_BINARY(data[0]), BYTE_TO_BINARY(data[1]), BYTE_TO_BINARY(data[2]));

                                //starting sequence: 0x10 -> 0x30 -> 0x50
                                //shutting down = 0x100

                            break;
        */

                        /*
                        case 0x2211:
                            printf ("Coolant temp unknown scale6: %i \n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x2213:
                            printf ("Coolant temp unknown scale7: %i \n", ((data[0] << 8) + data[1]));
                            break;

                        case 0x3002: //drivers wish?
                            printf ("Coolant temp unknown scale8 (1-949 no delay): %i \n", ((data[0] << 8) + data[1]));
                            break;

                        case 0xDF20:
                            printf ("Coolant temp unknown scale9 (Flips between 0x01 and 0x20 no delay): %i \n", data[1]);
                            break;

                        case 0xDF32:
                            printf ("Coolant temp unknown scale10 (Flips between a few distinct values, no delay): %i \n", ((data[0] << 8) + data[1]));
                            break;

                        default:
                            {
                            //unsigned int v = ((data[0] << 8) + data[1]);
                            //fprintf(rpm_file, "%04X %i %i\n", (vm.function_id << 8) + vm.function_param, curr_rpm, v);
                            }
                            break;
                            */


                    }
                    break; // 0xA6
                break;
              }
        }
    //qDebug() << "Number of measurements " << measurements.size();
    return measurements;
}

/*
        ******* A E **************
        
        Get ECU 2-byte DTC with some unknown additional data_
            can1  000FFFFE   [8]  CB 11 AE 31 14 00 00 00
            can1  01000021   [8]  8F 11 EE 31 95 30 4C 01
            can1  01000021   [8]  09 27 00 4D 02 28 00 4D
            can1  01000021   [8]  0A 08 12 00 4D 02 20 00
            can1  01000021   [8]  0B 4D 02 68 00 4D 08 14
            can1  01000021   [8]  4B 00 4D 01 00 00 00 00
            
            Interpreted as: ECU DTC: 9530 4c01 2700 4d02 2800 4d08 1200 4d02 2000 4d02 6800 4d08 1400 4d01 0000 0000

        Get ECU 2-byte DTC
            can1  000FFFFE   [8]  CB 11 AE 11 14 00 00 00
            can1  01000021   [8]  8F 11 EE 11 95 30 27 00
            can1  01000021   [8]  09 28 00 12 00 20 00 68
            can1  01000021   [8]  4B 00 14 00 00 00 00 00

            Interpreted as: ECU DTC: 9530 2700 2800 1200 2000 6800 1400 0000 0000



        ******* A F **************

        Clear ECU DTC. Get ECU DTC must be called before, or an error frame will be sent.
            can1  000FFFFE   [8]  CB 11 AF 11 00 00 00 00
            can1  01000021   [8]  CB 11 EF 11 00 00 00 00

            on error:

            can1  000FFFFE   [8]  CB 11 AF 11 00 00 00 00
            can1  01000021   [8]  CC 11 7F AF 22 00 00 00

            Interpreted as: OK

        ******* B 9 **************

        Unknown (immo related?)
            can1  000FFFFE   [8]  CB 11 B9 04 00 00 00 00
            can1  01000021   [8]  CC 11 F9 04 02 00 00 00
            
            Interpreted as: 02 00 00 00

        Unknown 06-09 gives the same result
            can1  000FFFFE   [8]  CB 11 B9 06 00 00 00 00
            can1  01000021   [8]  CD 11 F9 06 00 00 00 00

            Interpreted as: 00 00 00 00

        Unknown all zeros
            can1  000FFFFE   [8]  CB 11 B9 E0 00 00 00 00
            can1  01000021   [8]  8F 11 F9 E0 00 00 00 00
            can1  01000021   [8]  09 00 00 00 00 00 00 00
            can1  01000021   [8]  0A 00 00 00 00 00 00 00
            can1  01000021   [8]  4C 00 00 00 00 00 00 00
        
            Interpreted as: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00


        ECU Diagnostic Part Number

            can1  000FFFFE   [8]  CB 11 B9 F0 00 00 00 00
            can1  01000021   [8]  8F 11 F9 F0 00 30 63 77
            can1  01000021   [8]  09 33 20 20 41 08 66 74
            can1  01000021   [8]  4C 47 20 20 41 00 00 00
            
            Interpreted as: 003063773320204108667447202041000000
            


        Unknown but looks like a date
            can1  000FFFFE   [8]  CB 11 B9 F1 00 00 00 00  
            can1  01000021   [8]  8F 11 F9 F1 19 99 10 22
            can1  01000021   [8]  4B 11 30 00 00 00 00 00
            
            Interpreted as: 1999-10-22 11:30


        Unknown
            can1  000FFFFE   [8]  CB 11 B9 F2 00 00 00 00
            can1  01000021   [8]  8F 11 F9 F2 56 56 30 30
            can1  01000021   [8]  09 33 30 30 30 35 30 31
            can1  01000021   [8]  0A 20 20 20 20 20 20 00
            can1  01000021   [8]  0B 00 00 00 00 00 00 00
            can1  01000021   [8]  4F 00 00 00 00 00 00 00
            
            Interpreted as: 56 56 30 30 33 30 30 30 35 30 31 20 20 20 20 20 20 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
                    string: VV003000501   

        Unknown but looks like a data_ (Firmware version date?)
            can1  000FFFFE   [8]  CB 11 B9 F3 00 00 00 00
            can1  01000021   [8]  8F 11 F9 F3 20 03 11 13
            can1  01000021   [8]  4B 00 00 00 00 00 00 00

                Interpreted as:  2003-11-13
    
        Unknown
            can1  000FFFFE   [8]  CB 11 B9 F4 00 00 00 00
            can1  01000021   [8]  CD 11 F9 F4 1E 1E 00 00

        ECU Software Part Number
            can1  000FFFFE   [8]  CB 11 B9 F5 00 00 00 00
            can1  01000021   [8]  8F 11 F9 F5 00 03 58 69
            can1  01000021   [8]  09 40 50 30 31 00 0F A0
            can1  01000021   [8]  0A 00 00 03 80 89 68 50
            can1  01000021   [8]  4E 30 31 00 08 00 00 00

            Interpreted as: 0003586940503031000fa00000038089685030310008000000

        ECU Hardware Serial Number
            can1  000FFFFE   [8]  CB 11 B9 F8 00 00 00 00
            can1  01000021   [8]  8F 11 F9 F8 00 00 00 09
            can1  01000021   [8]  4A 55 89 00 00 00 00 00

            Interpreted as: 0000000955890000000000

    */
