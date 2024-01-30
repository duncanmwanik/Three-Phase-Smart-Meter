import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

Widget box(int line, int status, double voltage, double current) {
  return Container(
    margin: EdgeInsets.symmetric(horizontal: 20, vertical: 5),
    padding: EdgeInsets.symmetric(horizontal: 30, vertical: 10),
    width: double.maxFinite,
    decoration: BoxDecoration(color: Colors.white10, borderRadius: BorderRadius.circular(30)),
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Text('Phase $line', style: TextStyle(fontWeight: FontWeight.w900, fontSize: 22, color: Colors.white)),
            CupertinoSwitch(
              activeColor: Colors.blue,
              value: status == 1 ? true : false,
              onChanged: (value) async {
                await FirebaseDatabase.instance.ref().child('lines/line$line').update(getJsonMap({'status': value ? 1 : 0}));
              },
            )
          ],
        ),
        Divider(color: Colors.white30),
        Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            SizedBox(width: 50, child: Text('V  =  ', style: TextStyle(fontWeight: FontWeight.w700, fontSize: 25, color: Colors.white))),
            Container(
              padding: EdgeInsets.symmetric(horizontal: 10, vertical: 5),
              decoration: BoxDecoration(borderRadius: BorderRadius.circular(10), border: Border.all(color: Colors.white10)),
              child: Text(
                '$voltage V',
                style: TextStyle(fontWeight: FontWeight.w700, fontSize: 20, color: Colors.orange),
              ),
            ),
          ],
        ),
        SizedBox(height: 5),
        Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            SizedBox(width: 50, child: Text('I  = ', style: TextStyle(fontWeight: FontWeight.w700, fontSize: 25, color: Colors.white))),
            Container(
              padding: EdgeInsets.symmetric(horizontal: 10, vertical: 5),
              decoration: BoxDecoration(borderRadius: BorderRadius.circular(10), border: Border.all(color: Colors.white10)),
              child: Text(
                '$current A',
                style: TextStyle(fontWeight: FontWeight.w700, fontSize: 20, color: Colors.cyan),
              ),
            ),
          ],
        ),
        SizedBox(height: 5),
        Row(
          mainAxisSize: MainAxisSize.min,
          children: [
            SizedBox(width: 50, child: Text('P  = ', style: TextStyle(fontWeight: FontWeight.w700, fontSize: 25, color: Colors.white))),
            Container(
              padding: EdgeInsets.symmetric(horizontal: 10, vertical: 5),
              decoration: BoxDecoration(borderRadius: BorderRadius.circular(10), border: Border.all(color: Colors.white10)),
              child: Text(
                '${(voltage * current).round()} W',
                style: TextStyle(fontWeight: FontWeight.w700, fontSize: 20, color: Colors.greenAccent.shade400),
              ),
            ),
          ],
        ),
      ],
    ),
  );
}

Map<String, dynamic> getJsonMap(Map data) {
  return Map<String, dynamic>.from(data);
}
