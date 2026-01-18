import * as fs from "fs";
import * as path from "path";

import {CompilationUnit, parse_compilation_unit, Parser, parser_init} from "./parser";
import {Binder, binder_bind, binder_init, BoundProgram} from "./binder";
import {emit_program, Emitter, emitter_init} from "./c_emitter";

const files: string[] = [
    path.join(__dirname, "..", "input", "panic.lop"),
    path.join(__dirname, "..", "input", "char.lop"),
    path.join(__dirname, "..", "input", "main.lop"),
    path.join(__dirname, "..", "input", "list.lop"),
    path.join(__dirname, "..", "input", "lexer.lop"),
    path.join(__dirname, "..", "input", "parser.lop"),
    path.join(__dirname, "..", "input", "conversion.lop"),
    path.join(__dirname, "..", "input", "scope.lop"),
    path.join(__dirname, "..", "input", "binder.lop"),
];

const units: CompilationUnit[] = [];

for (const filename of files) {
    const content: string = fs.readFileSync(filename, "utf-8");
    const parser: Parser = parser_init(filename, content, content.length);
    const unit: CompilationUnit = parse_compilation_unit(parser);
    units.push(unit);
}

const outputFilename: string = path.join(__dirname, "..", "runtime", "main.c");

const binder: Binder = binder_init(units);
const program: BoundProgram = binder_bind(binder);

const stream: fs.WriteStream = fs.createWriteStream(outputFilename);
const emitter: Emitter = emitter_init(stream);

emit_program(emitter, program);