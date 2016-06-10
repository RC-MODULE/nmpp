import from "easynmc/easynmc.mlb";

/* Declare 2 circular buffers for stdio */
const EASYNMC_IOBUFLEN = 128;
EASYNMC_CBUF(".easynmc_stdin",  _easynmc_stdin_hdr,  _easynmc_stdin_data,  EASYNMC_IOBUFLEN);
EASYNMC_CBUF(".easynmc_stdout", _easynmc_stdout_hdr, _easynmc_stdout_data, EASYNMC_IOBUFLEN);
EASYNMC_ARGS(128);

/* Reserve 128 32-bit words for arguments */

