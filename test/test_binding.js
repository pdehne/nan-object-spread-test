const assert = require("assert");

// Pure JavaScript

const sampleObject = {};

sampleObject.stringProp = "Hello World";
assert(sampleObject.stringProp === "Hello World", "unexpected sampleObject.stringProp value");

sampleObject.numberProp = 3.1415926536;
assert(sampleObject.numberProp === 3.1415926536, "unexpected sampleObject.numberProp value");

spreadSampleObject = {...sampleObject};
assert(spreadSampleObject.stringProp === "Hello World", "unexpected spreadSampleObject.stringProp value");
assert(spreadSampleObject.numberProp === 3.1415926536, "unexpected spreadSampleObject.numberProp value");

// NAN addon

const addon = require("../lib/binding.js");
assert(addon, "addon is undefined");
assert(addon.SampleObject, "SampleObject is undefined");

const addonSampleObject = new addon.SampleObject();
assert(addonSampleObject);

addonSampleObject.stringProp = "Hello World";
assert(addonSampleObject.stringProp === "Hello World", "unexpected addonSampleObject.stringProp value");

addonSampleObject.numberProp = 3.1415926536;
assert(addonSampleObject.numberProp === 3.1415926536, "unexpected addonSampleObject.numberProp value");

const spreadAddonSampleObject = {...addonSampleObject};
assert(spreadAddonSampleObject.stringProp === "Hello World", "unexpected spreadAddonSampleObject.stringProp value");
assert(spreadAddonSampleObject.numberProp === 3.1415926536, "unexpected spreadAddonSampleObject.numberProp value");

console.log("Tests passed!");
