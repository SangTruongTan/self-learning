# Prerequisites
```bash
sudo apt-get install lttng-tools liblttng-ust-dev
```

# How to collect traces
To record the events of the user application:

## Run the application with a few arguments:

```bash
./hello world and beyond
```

You see:
```bash
Hello, World!
Press Enter to continue...
```

## Start an LTTng session daemon:

```bash
lttng-sessiond --daemonize
```
Note: A session daemon might already be running, for example as a service that the service manager of your distribution started.

## List the available user space tracepoints:

```bash
lttng list --userspace
```

You see the hello_world:my_first_tracepoint tracepoint listed under the `./hello process`.

## Create a recording session:

```bash
lttng create my-user-space-session
```

## Create a recording event rule which matches user space tracepoint events named hello_world:my_first_tracepoint:

```bash
lttng enable-event --userspace hello_world:my_first_tracepoint
```

## Start recording:

```bash
lttng start
```

Go back to the running hello application and press Enter.

The program executes all lttng_ust_tracepoint() instrumentation points, emitting events as the event rule you created in step 5 matches them, and exits.

## Destroy the current recording session:

```bash
lttng destroy
```

# Viewer the traces
```bash
babeltrace ~/lttng-traces/my-session-20240617-152129/ -o text --output ./trace.txt
```
