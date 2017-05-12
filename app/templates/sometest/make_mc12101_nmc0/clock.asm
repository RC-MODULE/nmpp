//----------------------------------------------------------------
//
// clock.asm,              1997-2016 (c) RC Module Ltd.
// nm6407, clock function realisation file
//
//----------------------------------------------------------------

const ADR_Timer0     = 4000_0800h;
const ADR_TimerMode0 = 4000_0802h;
const ADR_Timer1     = 4000_0804h;
const ADR_TimerMode1 = 4000_0806h;

global _clock : label;
global clock_initialize : label;

begin text

<clock_initialize>
    with gr7 = false;
    [ADR_Timer1] = gr7;
    gr7 = 11_1_1b;
    delayed return;
    [ADR_TimerMode1] = gr7;

end text;

    // called before main function.

begin init
        // call to initializing functions before the call to 'main'
    call clock_initialize;
end init;

begin text

<_clock>
	delayed return;
    gr7 = [ADR_Timer1];

end text;
