/*
  See https://www.RoxXxtar.com/bmc for more details
  Copyright (c) 2020 RoxXxtar.com
  Licensed under the MIT license.
  See LICENSE file in the project root for full license information.

  Value/Sketch Stream is just a way for BMC to send data to the sketch via callbacks
  For example, when a button has a MIDI Control Change event, when the event is handled
  BMC will trigger a callback (if set) with the data of the MIDI message that was sent
  This is useful for displays, you can display the current value of a CC as it changes.
*/
#include <BMC.h>

// Value stream handlers
// used to send data to the sketch for use with displays
void BMC::streamToSketch(uint8_t t_id, int t_value){
  if(callback.valueStream){
    char str[2] = " ";
    streamToSketch(t_id, t_value, str);
  }
}
void BMC::streamToSketch(uint8_t t_id, int t_value, const char* str){
  if(callback.valueStream){
    String buff = str;
    uint8_t length = buff.length()+1;
    length = constrain(length,0,30);
    char output[length];
    buff.toCharArray(output, length);
    streamToSketch(t_id, t_value, str);
  }
}
void BMC::streamToSketch(uint8_t t_id, int t_value, char* str){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = t_id;
    item.value = t_value;

    if(t_id==BMC_ITEM_ID_PAGE && strlen(BMC_STREAM_TEMPL_PAGE)+strlen(str)<30){
      sprintf(item.name, BMC_STREAM_TEMPL_PAGE, (uint8_t) (t_value+1), str);
    } else if(t_id==BMC_ITEM_ID_PRESET && strlen(BMC_STREAM_TEMPL_PRESET)+strlen(str)<30){
      sprintf(item.name, BMC_STREAM_TEMPL_PRESET,(uint8_t) (t_value+1), str);
    } else if(t_id==BMC_ITEM_ID_SETLIST && strlen(BMC_STREAM_TEMPL_SETLIST)+strlen(str)<30){
      sprintf(item.name, BMC_STREAM_TEMPL_SETLIST,(uint8_t) (t_value+1), str);
    } else if(t_id==BMC_ITEM_ID_SETLIST_SONG && strlen(BMC_STREAM_TEMPL_SETLIST_SONG)+strlen(str)<30){
      sprintf(item.name, BMC_STREAM_TEMPL_SETLIST_SONG,(uint8_t) (t_value+1), str);
    } else if(strlen(str)<30){
      strcpy(item.name, str);
    }
    callback.valueStream(item);
  }
}
void BMC::streamMidi(uint8_t status, uint8_t channel, uint8_t data1, uint8_t data2){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = status;
    item.value = data2==255?data1:data2;
    if(data2==255){
      item.data = (data1<<8) | (status | channel);
    } else {
      item.data = (data2<<16) | (data1<<8) | (status | channel);
    }
    switch(status){
      case BMC_MIDI_CONTROL_CHANGE:
        sprintf(item.name, BMC_STREAM_TEMPL_MIDI_CC, channel, data1, data2);
        break;
      case BMC_MIDI_NOTE_ON:
        sprintf(item.name, BMC_STREAM_TEMPL_MIDI_NOTE_ON, channel, data1, data2);
        break;
      case BMC_MIDI_NOTE_OFF:
        sprintf(item.name, BMC_STREAM_TEMPL_MIDI_NOTE_ON, channel, data1, data2);
        break;
      case BMC_MIDI_PROGRAM_CHANGE:
        sprintf(item.name, BMC_STREAM_TEMPL_MIDI_PC, channel, data1);
        break;
    }
    callback.valueStream(item);
  }
}
void BMC::streamRawValue(uint16_t t_value){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = 0;
    item.value = t_value;
    item.data = t_value;
    sprintf(item.name, "%03u", t_value);
    callback.valueStream(item);
  }
}
void BMC::streamTmpScrollerPage(uint8_t value){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = BMC_ITEM_ID_PAGE;
    item.value = value;
    item.data = value;
    sprintf(item.name,BMC_STREAM_TEMPL_TMP_PAGE_SCROLL,value);
    callback.valueStream(item);
  }
}
void BMC::streamTmpScrollerPreset(uint8_t value){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = BMC_ITEM_ID_PRESET;
    item.value = value;
    item.data = value;
    sprintf(item.name,BMC_STREAM_TEMPL_TMP_PRESET_SCROLL,value);
    callback.valueStream(item);
  }
}
void BMC::streamMidiProgram(uint8_t channel, uint8_t program){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = BMC_ITEM_ID_MIDI_PROGRAM;
    item.value = program;
    item.data = (program<<8) | BMC_ITEM_ID_MIDI_PROGRAM |channel;
    sprintf(item.name,BMC_STREAM_TEMPL_MIDI_PC,channel, program);
    callback.valueStream(item);
  }
}
void BMC::streamMidiControl(uint8_t channel, uint8_t control, uint8_t value){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = BMC_ITEM_ID_MIDI_CONTROL;
    item.value = value;
    item.data = (value<<16) | (control<<8) | BMC_ITEM_ID_MIDI_CONTROL | channel;
    sprintf(item.name,BMC_STREAM_TEMPL_MIDI_CC,channel, control,value);
    callback.valueStream(item);
  }
}
void BMC::streamMidiClockBPM(uint16_t bpm){
  if(callback.valueStream){
    BMCValueStream item;
    item.id = BMC_ITEM_ID_MIDI_CLOCK;
    item.value = bpm;
    item.data = bpm;
    sprintf(item.name, BMC_STREAM_TEMPL_MIDI_CLOCK_BPM, bpm);
    callback.valueStream(item);
  }
}
