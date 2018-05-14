import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.stream.IntStream;

public class Solution {
    static class Graph {
        Map<Integer, List<Integer>> neighs;
        Map<Set<Integer>, Integer> edges;

        Graph(Map<Integer, List<Integer>> neighs, Map<Set<Integer>, Integer> edges) {
            this.neighs = neighs;
            this.edges = edges;
        }
    }

    static class Dist implements Comparable<Dist> {
        int value;
        int vertex;

        Dist(int value, int vertex) {
            this.value = value;
            this.vertex = vertex;
        }

        @Override
        public int compareTo(Dist other) {
            return this.value - other.value;
        }

        @Override
        public boolean equals(Object other) {
            return this.vertex == ((Dist)other).vertex;
        }
    }

    static int[] shortestReach(int n, int[][] edges, int s) {
        int[] result = new int[n - 1];
        int i = 0;

        SortedMap<Integer, Integer> dist = distances(n, graph(edges), s);

        for (int v : dist.keySet()) {
            if (v == s) continue;
            int d = dist.get(v);
            result[i] = d == Integer.MAX_VALUE ? -1 : d;
            i++;
        }

        return result;
    }

    private static SortedMap<Integer, Integer> distances(int vCount, Graph g, int source) {
        Queue<Dist> q = new PriorityQueue<>();
        Map<Integer, Integer> dist = new HashMap<>();

        IntStream.rangeClosed(1, vCount).forEach(i -> {
            int distValue = i == source ? 0 : Integer.MAX_VALUE;
            q.add(new Dist(distValue, i));
            dist.put(i, distValue);
        });

        while (q.size() > 0 && q.peek().value < Integer.MAX_VALUE) {
            int current = q.poll().vertex;

            for (int adjacent : g.neighs.get(current)) {
                int alt = dist.get(current) + g.edges.get(edge(current, adjacent));

                if (alt < dist.get(adjacent)) {
                    q.remove(new Dist(dist.get(adjacent), adjacent));
                    q.add(new Dist(alt, adjacent));
                    dist.put(adjacent, alt);
                }
            }
        }

        return new TreeMap<>(dist);
    }

    private static Graph graph(int[][] rows) {
        Map<Integer, List<Integer>> neighs = new HashMap<>();
        Map<Set<Integer>, Integer> edges = new HashMap<>();

        for (int[] triplet : rows) {
            if (!neighs.containsKey(triplet[0])) {
                neighs.put(triplet[0], new LinkedList<>());
            }

            if (!neighs.containsKey(triplet[1])) {
                neighs.put(triplet[1], new LinkedList<>());
            }

            neighs.get(triplet[0]).add(triplet[1]);
            neighs.get(triplet[1]).add(triplet[0]);

            Set<Integer> e = edge(triplet[0], triplet[1]);
            if (!edges.containsKey(e) || edges.get(e) > triplet[2]) {
                edges.put(edge(triplet[0], triplet[1]), triplet[2]);
            }
        }

        return new Graph(neighs, edges);
    }

    private static Set<Integer> edge(int vertex1, int vertex2) {
        Set<Integer> result = new HashSet<>();
        result.add(vertex1);
        result.add(vertex2);
        return result;
    }

    private static final Scanner scanner = new Scanner("1\n" +
            "20 54\n" +
            "1 7 45\n" +
            "2 14 15\n" +
            "3 7 29\n" +
            "4 1 48\n" +
            "5 1 66\n" +
            "6 7 17\n" +
            "7 14 15\n" +
            "8 14 43\n" +
            "9 1 27\n" +
            "10 1 33\n" +
            "11 14 64\n" +
            "12 14 27\n" +
            "13 7 66\n" +
            "14 7 54\n" +
            "15 14 56\n" +
            "16 7 21\n" +
            "17 1 20\n" +
            "18 1 34\n" +
            "19 7 52\n" +
            "20 14 14\n" +
            "9 14 9\n" +
            "15 1 39\n" +
            "12 1 24\n" +
            "9 1 16\n" +
            "1 2 33\n" +
            "18 1 46\n" +
            "9 1 28\n" +
            "15 14 3\n" +
            "12 1 27\n" +
            "1 2 5\n" +
            "15 1 34\n" +
            "1 2 28\n" +
            "9 7 16\n" +
            "3 7 23\n" +
            "9 7 21\n" +
            "9 14 19\n" +
            "3 1 20\n" +
            "3 1 5\n" +
            "12 14 19\n" +
            "3 14 2\n" +
            "12 1 46\n" +
            "3 14 5\n" +
            "9 14 44\n" +
            "6 14 26\n" +
            "9 14 16\n" +
            "9 14 34\n" +
            "6 7 42\n" +
            "3 14 27\n" +
            "1 7 9\n" +
            "1 7 41\n" +
            "15 14 19\n" +
            "12 7 13\n" +
            "3 7 10\n" +
            "1 7 2\n" +
            "17\n");

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("/dev/stdout"));

        int t = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

        for (int tItr = 0; tItr < t; tItr++) {
            String[] nm = scanner.nextLine().split(" ");

            int n = Integer.parseInt(nm[0]);

            int m = Integer.parseInt(nm[1]);

            int[][] edges = new int[m][3];

            for (int i = 0; i < m; i++) {
                String[] edgesRowItems = scanner.nextLine().split(" ");
                scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

                for (int j = 0; j < 3; j++) {
                    int edgesItem = Integer.parseInt(edgesRowItems[j]);
                    edges[i][j] = edgesItem;
                }
            }

            int s = scanner.nextInt();
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])?");

            int[] result = shortestReach(n, edges, s);

            for (int i = 0; i < result.length; i++) {
                bufferedWriter.write(String.valueOf(result[i]));

                if (i != result.length - 1) {
                    bufferedWriter.write(" ");
                }
            }

            bufferedWriter.newLine();
        }

        bufferedWriter.close();

        scanner.close();
    }
}
