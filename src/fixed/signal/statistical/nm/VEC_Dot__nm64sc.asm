import from macros.mlb;
begin ".text_nmplv"
//------------------------------------------------------------------------------------------------
//  ��������� ��������� ����������� �������� ����.V1*V2
//  time=70 ������ �� ����������� �����.
//------------------------------------------------------------------------------------------------
//! \fn void nmppsDotProd(nm64sc *pSrcVec1, nm64sc *pSrcVec2, int nSize,  nm64sc *pnRes);
//! 
//! \perfinclude _nmppsDotProd__F6nm64scP6nm64scPi6nm64scP.html 
//------------------------------------------------------------------------------------------------
global _nmppsDotProd__F6nm64scP6nm64scPi6nm64scP:label;
global _void._.8.8nmppsDotProd.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._class._nm64sc._.0.2 :label;
tmp: word[16];
      <_nmppsDotProd__F6nm64scP6nm64scPi6nm64scP>
<_void._.8.8nmppsDotProd.1class._nm64sc._.0.9._class._nm64sc._.0.9._int.9._class._nm64sc._.0.2>
   ar5=ar7-2 with gr7=false;
   PUSH_REGS();
   ar0=[--ar5];  // Vec1
   ar2=[--ar5];  // Vec2
   gr6=[--ar5];  // L=Length
   ar6=[--ar5];  // Dst ���������
.wait;  nb1=gr7; wtw;ar5=ar6;
   rep 2 data=[ar6] with data-data;
   rep 2 [ar6++]=afifo;  // dts=0;
   sb=gr7;
.branch;
   rep 1 wfifo=[ar2++],ftw; // X
   ar1=ar0;
   ar4=tmp; // long[4] 3a
   ar3=ar4;
   rep 1 data=[ar0++]with data;      // a  27
   rep 1 [ar4++]=afifo;              // a  27
   rep 1 data=[ar0++] with 0-data;   // -b
   rep 1 [ar4++]=afifo with 0-afifo; // b   27
   rep 1 [ar4++]=afifo;              // b
   rep 1 data=[ar1] with data;       // a
   rep 1 [ar4++]=afifo;              // 27
   rep 1 wfifo=[ar2++];  // Y
   ar6=ar5;
.wait;nb1=gr7 with gr6--;wtw;.branch;  // matr=X  36
   if =0 delayed skip Prodv1;
   rep 2 data=[ar3++],ftw with vsum,data,0;  //  a*X, -b*X 43
   rep 2 data=[ar6++] with data+afifo;  // -b*Y, a*Y 43
<prodV0>
   ar6=ar5;  // 43
   rep 1 wfifo=[ar2++];  // X
.wait;nb1=gr7;wtw;.branch;  // matr=Y 
   rep 2 data=[ar3++],ftw with vsum,data,afifo;  // 
   rep 2 [ar6++]=afifo;  
   ar1=ar0;
   ar4=tmp; // long[4] 3a
   ar3=ar4;
   rep 1 data=[ar0++]with data;      // a  27
   rep 1 [ar4++]=afifo;              // a  27
   rep 1 data=[ar0++] with 0-data;   // -b
   rep 1 [ar4++]=afifo with 0-afifo; // b   27
   rep 1 [ar4++]=afifo;              // b
   rep 1 data=[ar1] with data;       // a
   rep 1 [ar4++]=afifo;              // 27
   rep 1 wfifo=[ar2++];  // Y
   ar6=ar5;
.wait;nb1=gr7 with gr6--;wtw;.branch;  // matr=X  36
   if > delayed skip prodV0;
   rep 2 data=[ar3++],ftw with vsum,data,0;  //  a*X, -b*X 43
   rep 2 data=[ar6++] with data+afifo;  // -b*Y, a*Y 43
<Prodv1>
   ar6=ar5;  
.wait;nb1=gr7;wtw;.branch;  // matr=Y 
   rep 2 data=[ar3++] with vsum,data,afifo;  
   rep 2 [ar6++]=afifo;  
 POP_REGS(); 
 delayed return;
 gr7=[tmp];nul;
end ".text_nmplv";
