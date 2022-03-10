//***************************************************************************/
//*                                                                         */
//*                    Neuroprocessor NM6403 SDK v.1.2                      */
//*                                                                         */
//*				Signed Fixed Point 32-bit Routine                           */
//*                                                                         */
//*           ���������� �������� ����� � ������������� �������             */
//*                                                                         */
//*                                                                         */
//*                1999 (c) RC Module Inc., Moscow, Russia                  */
//***************************************************************************/

const FIXPOINT=16; //��������� �������� ����� � 32-� ��������� �����
const N=9;//804-����� - ��������� ������������ ������ ������� �������� �������� 
//const N=10//1608-�����
const PI2 = (6487ed51h >> (30-FIXPOINT)) ;//PI2=90 ����.
//const MAXINDEX=PI2 >> (FIXPOINT-N);//������ ������� �������� ��������

extern FixSinDat:word;

begin ".text_nmpl�"

//! \fn int nmppcTblFixCos32(int nArg)
//! 
//! \perfinclude _nmppcTblFixCos32__Fi.html
global _nmppcTblFixCos32:label;
<_nmppcTblFixCos32>
.branch;
	ar5 = sp-2;
	gr7 = [--ar5];
	push ar1,gr1;
	gr1 = PI2;
	with gr7=gr1-gr7;
	//���������� ������ ����
	if >= delayed skip 4 with gr1=gr7;
		ar1=FixSinDat ;
	gr1=-gr1;
	nul;
	//����������� �������� ,�������������� ������� ����
		gr1 >>=(FIXPOINT-N);	//���������� ������� �� �������� ����
		gr7=[ar1+=gr1] with gr7;
	//��������� ����� ���������	 
	if >= delayed skip 4;
		pop ar1,gr1;	
		nul;
	gr7=-gr7;
	nul;

return;



.wait;
end ".text_nmpl�";
