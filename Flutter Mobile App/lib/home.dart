import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

import 'all_relays.dart';
import 'box.dart';

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key});

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xff1f1f1f),
      appBar: AppBar(
        backgroundColor: const Color(0xff1f1f1f),
        title: Text('Power App'),
      ),
      body: StreamBuilder(
          stream: FirebaseDatabase.instance.ref().child('lines').onValue,
          builder: (context, snapshot) {
            if (snapshot.data != null) {
              Map data = snapshot.data!.snapshot.value as Map;
              return ScrollConfiguration(
                behavior: const ScrollBehavior().copyWith(overscroll: false),
                child: ListView(
                  shrinkWrap: true,
                  children: <Widget>[
                    allRelaySwitch(data['all'] != null ? data['all']['status'] : 0),
                    box(1, data['line1']['status'], double.parse(data['line1']['voltage'].toString()), double.parse(data['line1']['current'].toString())),
                    box(2, data['line2']['status'], double.parse(data['line2']['voltage'].toString()), double.parse(data['line2']['current'].toString())),
                    box(3, data['line3']['status'], double.parse(data['line3']['voltage'].toString()), double.parse(data['line3']['current'].toString())),
                    SizedBox(height: 50),
                  ],
                ),
              );
            } else {
              return Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Container(
                    margin: EdgeInsets.symmetric(vertical: 100),
                    padding: EdgeInsets.symmetric(horizontal: 30, vertical: 20),
                    decoration: BoxDecoration(color: Colors.white10, borderRadius: BorderRadius.circular(10)),
                    child: Text(
                      'Just a minute, loading data...',
                      style: TextStyle(fontWeight: FontWeight.w500, fontSize: 16, color: Colors.white),
                    ),
                  ),
                ],
              );
            }
          }),
    );
  }
}
