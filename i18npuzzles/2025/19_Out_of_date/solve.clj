#!/usr/bin/env bb

(require '[clojure.string :as str])

(def input (slurp *in*))
(def lines (str/split input #"\n"))
(prn lines)
