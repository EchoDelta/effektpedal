const portAudio = require("naudiodon");
const through2 = require("through2");

const partition = (array, n) =>
  array.length ? [array.splice(0, n)].concat(partition(array, n)) : [];

const timeout = (s) => new Promise((resolve) => setTimeout(() => resolve(), s));

// parse command line arguments to object
const args = partition(process.argv.slice(2), 2).reduce((acc, [key, value]) => {
  acc[key.replace(/^-/, "")] = value;
  return acc;
}, {});

const [mic] = portAudio
  .getDevices()
  .filter((device) => device.name.toLowerCase().includes("mic"));

const [speaker] = portAudio
  .getDevices()
  .filter((device) => device.name.toLowerCase().includes("speaker"));

if (!args.timeout) {
  console.error(
    [
      "usage: node pifect.js -timeout 2000\n",
      "  -debug true\tdebug attached audio devices",
      "  -timeout <ms>\twill record and play back data for <ms> milliseconds",
    ].join("\n")
  );

  process.exit();
}

if (args.debug) {
  console.log("found audio devices", portAudio.getDevices());
  console.log("chose mic", mic);
  console.log("chose speaker", speaker);
  process.exit(0);
}

const input = new portAudio.AudioIO({
  inOptions: {
    channelCount: mic.maxInputChannels,
    sampleFormat: portAudio.SampleFormat16Bit,
    sampleRate: 44100,
    deviceId: mic.id,
    closeOnError: false,
  },
});

const output = new portAudio.AudioIO({
  outOptions: {
    channelCount: 2,
    sampleFormat: portAudio.SampleFormat16Bit,
    sampleRate: speaker.defaultSampleRate / 2,
    deviceId: speaker.id,
    closeOnError: false,
  },
});

output.start();
input.start();

input
  .pipe(
    through2(async function (chunk, enc, callback) {
      await timeout(100);
      this.push(chunk);
      callback();
    })
  )
  .pipe(output);

if (args.timeout) {
  const timeout = Number(args.timeout);
  console.log("Will timeout after", timeout);
  setTimeout(() => input.quit(process.exit(0), timeout), timeout);
}
