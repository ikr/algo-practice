#!/usr/bin/env bb

(require '[babashka.process :refer [shell]])

(def input (slurp *in*))

(shell "rm" "-rf" "chrono-tz")
(shell "git"
       "clone"
       "--branch"
       "v0.10.4"
       "--single-branch"
       "https://github.com/chronotope/chrono-tz.git")
(shell {:dir "chrono-tz"} "git" "submodule" "init")
(shell {:dir "chrono-tz"} "git" "submodule" "update")

(doseq [tv ["2018c" "2018g" "2021b" "2023d"]]
  (shell {:dir "chrono-tz/chrono-tz/tz"} "git" "checkout" tv)
  (shell {:dir "local_time_to_utc"} "cargo" "clean")
  (shell {:dir "local_time_to_utc"} "cargo" "build")
  (shell {:in input, :out (str tv ".txt")} "local_time_to_utc/target/debug/local_time_to_utc"))
