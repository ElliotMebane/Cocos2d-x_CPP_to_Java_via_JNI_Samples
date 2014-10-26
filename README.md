Cocos2d-x_CPP_to_Java_via_JNI_Samples
=====================================

Samples of communication to Java from C++ via JNI. Using Cocos2d-x v3.2 and newer (non-deprecated) approaches. 

This sample demonstrates the use of JNI for C++ to Java communication with Cocos2d-x v3.2. The foundation of the sample was this blog post by Stefan Nguyen:<br/>
http://stnguyen.com/cocos2d-x/call-java-functions-from-cpp.html

It was a challenge to get C++ to Java communication working with the latest version of Cocos2d-x because Cocos2d-x v.3.0 introduced significant changes and as a result a lot of the tutorials I found on this topic were outdated or incomplete. I prefer complete working samples over tutorials when I'm learning new code concepts. I hope this working sample helps make things a lot easier for you than they were for me as I tried to figure this stuff out! This sample has been compiled and tested but please notify me if you discover any problems. 

JNI communication<br/>
4 buttons that launch native Java dialog windows.
<ul>
<li>Calling a Java method from C++</li>
<li>Passing an int from C++ to Java</li>
<li>Passing an int from C++ to Java method and receiving a String return</li>
<li>Passing a String and an int from C++ to Java method and receiving a String return</li>
</ul>

Java Dialog<br/>
Resources that helped construct a solution to launch native Java dialogs:
<ul>
<li>http://stackoverflow.com/questions/13377300/how-to-show-dialog-from-a-static-method</li>
<li>http://stackoverflow.com/questions/12051973/how-to-display-custom-dialog-in-cocos2dxactivity</li>
<li>http://stackoverflow.com/questions/4336470/how-do-i-close-an-android-alertdialog</li>
<li>(Formatting Java method signatures. i.e., when to use semicolons) http://www.ibm.com/developerworks/java/tutorials/j-jni/j-jni.html#appendixa</li>
</ul>

Menu<br/>
<ul>
<li>I used simple MenuItem text-label buttons with callbacks as described in the 3.0 release notes:<br/>
<a href="https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md">https://github.com/cocos2d/cocos2d-x/blob/cocos2d-x-3.0/docs/RELEASE_NOTES.md</a>.</li>
<li>Similar samples are documented here:<br/> https://github.com/cocos2d/cocos2d-x/blob/v3/tests/cpp-tests/Classes/MenuTest/MenuTest.cpp.</li>
<li>I avoided methods that have been deprecated. I did not use the newest GUI options like Button, which would have looked better. They're documented here if you want them: <br/>
http://www.cocos2d-x.org/wiki/Cocos2D-X_New_GUI.</li>
</ul>

Dev/Test environment
<ul>
<li>Cocos2d-x 3.2</li>
<li>Mac/OSX 10.9.4</li>
<li>Eclipse Luna 4.4.0</li>
<li>Google Nexus 4 phone</li>
<li>Android 4.4.2</li>
<li>(XCode6.0 Beta)*<br/>
* Tested in XCode iPhone simulator to verify cross-platform compilation. Android-exclusive conditionals are verified. When publishing on iOS no dialog launcher menu nor dialogs are displayed.</li>
</ul>
I haven't made a sample of communication from Java to C++, but I may apply the info from Nguyen's second post and make a sample. <br/>
http://stnguyen.com/cocos2d-x/call-cpp-functions-from-java.html
