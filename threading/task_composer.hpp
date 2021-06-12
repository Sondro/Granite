/* Copyright (c) 2017-2020 Hans-Kristian Arntzen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "thread_group.hpp"

// Designed to compose a series of pipelined tasks.

namespace Granite
{
class TaskComposer
{
public:
	explicit TaskComposer(ThreadGroup &group);
	void set_incoming_task(TaskGroupHandle group);
	TaskGroup &begin_pipeline_stage();
	TaskGroup &get_group();

	// Returns a waitable handle that can be waited on.
	TaskGroupHandle get_outgoing_task();
	TaskGroupHandle get_pipeline_stage_dependency();
	ThreadGroup &get_thread_group();

	// If an indirect handle is called, the next pipeline stage will implicitly depend
	// on the indirect handle. This is useful if a pipeline stage will spawn tasks on its own.
	// As long as the indirect handle is kept alive in child tasks, the next pipeline stage will not begin.
	TaskGroupHandle get_indirect_handle();

	void signal_task_on_completion(TaskGroup &task);

private:
	ThreadGroup &group;
	TaskGroupHandle current;
	TaskGroupHandle incoming_deps;
	TaskGroupHandle next_stage_deps;
};
}
