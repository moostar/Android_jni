package com.example.apple.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import java.util.ArrayList;

import cn.dpocket.youja.ClientNDK;
import cn.dpocket.youja.Student;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ClientNDK ndk = new ClientNDK();
        ndk.native_printf("value");
        ArrayList<Student> list = ndk.native_getListStudents();

        for(int i = 0 ;i < list.size();i ++){
            System.out.println("list" + list.get(i).toString());
        }
        ndk.printStuInfoAtNative(new Student(10,"csc"));
//        Student stu = ndk.nativeGetStudentInfo();
//        System.out.println(stu.toString());
        int value[][] = ndk.getTwoArray(0);

        System.out.println("value" + value);
        ndk.doCallBack();
    }
}
