import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

Widget allRelaySwitch(int status) {
  return Container(
    margin: EdgeInsets.only(left: 20, right: 20, top: 10, bottom: 5),
    padding: EdgeInsets.symmetric(horizontal: 30, vertical: 10),
    width: double.maxFinite,
    decoration: BoxDecoration(color: Colors.white10, borderRadius: BorderRadius.circular(20)),
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Text('All Phases', style: TextStyle(fontWeight: FontWeight.w900, fontSize: 22, color: Colors.white)),
            CupertinoSwitch(
              activeColor: Colors.blue,
              value: status == 1 ? true : false,
              onChanged: (value) async {
                await FirebaseDatabase.instance.ref().child('lines/all').update(getJsonMap({'status': value ? 1 : 0}));
		if(!value){
			await FirebaseDatabase.instance.ref().child('lines/line1').update(getJsonMap({'status': value ? 1 : 0}));
                	await FirebaseDatabase.instance.ref().child('lines/line2').update(getJsonMap({'status': value ? 1 : 0}));
                	await FirebaseDatabase.instance.ref().child('lines/line3').update(getJsonMap({'status': value ? 1 : 0}));
		}
                
              },
            )
          ],
        ),
      ],
    ),
  );
}

Map<String, dynamic> getJsonMap(Map data) {
  return Map<String, dynamic>.from(data);
}
