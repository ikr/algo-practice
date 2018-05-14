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
        SortedMap<Integer, Integer> dist = new TreeMap<>();

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

        return dist;
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

            edges.put(edge(triplet[0], triplet[1]), triplet[2]);
        }

        return new Graph(neighs, edges);
    }

    private static Set<Integer> edge(int vertex1, int vertex2) {
        Set<Integer> result = new HashSet<>();
        result.add(vertex1);
        result.add(vertex2);
        return result;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

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
