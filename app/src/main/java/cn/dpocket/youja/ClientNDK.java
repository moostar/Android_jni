package cn.dpocket.youja;

import java.util.ArrayList;

/**
 * Created by Apple on 16/5/9.
 */
public class ClientNDK {

//    public class Student
//    {
//        private int age ;
//        private String name ;
//        //构造函数，什么都不做
//        public Student(){ }
//
//        public Student(int age ,String name){
//            this.age = age ;
//            this.name = name ;
//        }
//
//        public int getAge() {
//            return age;
//        }
//        public void setAge(int age) {
//            this.age = age;
//        }
//        public String getName() {
//            return name;
//        }
//        public void setName(String name){
//            this.name = name;
//        }
//
//        public String toString(){
//            return "name --- >" + name + "  age --->" + age ;
//        }
//    }

    static{
        try {
            System.loadLibrary("app");
        }catch (UnsatisfiedLinkError e){
            System.out.println("err" + e);
        }
    }
    //1
    public native String native_printf(String value);

    //2
    public native int[][] getTwoArray(int dimon) ;



    //3 Native层回调的方法实现
    public void callback(String fromNative){
        System.out.println(" I was invoked by native method  ############# " + fromNative);
    };
    public native void doCallBack(); //Native层会调用callback()方法


//    public native Student nativeGetStudentInfo() ;


    public native void  printStuInfoAtNative(Student stu);

    public native ArrayList<Student> native_getListStudents();

}
