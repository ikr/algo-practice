#!/usr/bin/env bb

(require '[clojure.string :as str])

(def input (slurp *in*))
(def lines (str/split input #"\n"))
(def zones-vec (->> lines (map #(-> % (str/split #"; ") second)) vec))
(def zones (into #{} zones-vec))

(def tzdata-versions ["2018c" "2018g" "2021b" "2023d"])

(defn utc-vec [tzdata-version]
  (let [text (slurp (str tzdata-version ".txt"))
        lines (-> text (str/split #"\n") vec)]
    (map-indexed (fn [i t] [t (get zones-vec i)]) lines)))

(def utc-tuples-by-zone (->> tzdata-versions (map #(vector % (utc-vec %))) (into {})))
(def all-utc-tuples (->> utc-tuples-by-zone vals (apply concat)))
(def all-instants (->> utc-tuples-by-zone vals (map #(map first %)) (apply concat) (into #{})))

(def instants-by-zone
  (reduce (fn [acc [t z]] (update acc z #(conj % t)))
          (->> zones (map #(vector % #{})) (into {}))
          all-utc-tuples))

(defn in-all-zones? [t] (every? #(contains? % t) (vals instants-by-zone)))
(def result (->> all-instants (filter in-all-zones?) first))

(println result)
