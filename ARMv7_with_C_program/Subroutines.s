
   .global floatAvg
   .global exam3Agrade

/*r0= hw(the grade), R1= n(the number of hw) */

floatAvg:
   vldr s0,[r0]          @mov float into s0
   mov r4,#0

   b check

 add:
   vadd.f32 s1,s1,s0    @now add all the array here

   add r0,r0,#4
   vldr s0,[r0]         @grab the next point

   add  r4,r4,#1

 check:
   cmp r4,r1            @the end of loop after r1 attempts
   bne add

 end:
   vmov s2,r1
   vcvt.f32.s32 s2,s2   @convert s2  into a float

   vdiv.f32 s0,s1,s2
   
bx lr




/*r0 = exam1, r1=exam2 */
exam3Agrade:
   mov r3,#90           @the score prefer

 convertToFloat:        @setting up the floats from parameter 
   vmov s1,r0
   vcvt.f32.s32 s1,s1
   vmov s2,r1
   vcvt.f32.s32 s2,s2
   vmov s3,r3
   vcvt.f32.s32 s3,s3

 settingUP:            @setting up the percentage
   mov r4,#20
   mov r5,#25
   mov r6,#30          
   mov r7,#100         @to divide the percentage

   vmov s4,r4          @converting them into float
   vmov s5,r5
   vmov s6,r6
   vmov s7,r7
   vcvt.f32.s32 s4,s4
   vcvt.f32.s32 s5,s5
   vcvt.f32.s32 s6,s6
   vcvt.f32.s32 s7,s7

   vdiv.f32 s4,s4,s7   @s4 = 20/100
   vdiv.f32 s5,s5,s7   @s5 = 25/100
   vdiv.f32 s6,s6,s7   @s6 = 30/100 

 ToMultiply:
   vmul.f32 s0,s0,s5   @s0= hw*.25
   vmul.f32 s1,s1,s5   @s1=exam1*.25
   vmul.f32 s2,s2,s6   @s2-exam2*.30

 addThem:
   vadd.f32 s0,s0,s1   @adding all hw,exam1,exam2
   vadd.f32 s0,s0,s2

 subtract:
   vsub.f32 s0,s3,s0   @90-all added value

   vdiv.f32 s0,s0,s4   @overall/by .20of final exam

bx lr
