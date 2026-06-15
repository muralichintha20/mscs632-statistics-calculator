(*
 * statistics.ml
 * Basic Statistics Calculator (Functional Paradigm)
 *
 * Calculates mean, median, and mode for a list of integers using
 * immutable data and higher-order functions (List.fold_left, List.map,
 * List.filter, List.sort). No mutable state is used.
 *
 * Author: Murali Krishna Chintha
 * Course: MSCS-632 Advanced Programming Languages
 *)

(* Mean: fold the list into a running sum, then divide by the length.
   fold_left avoids any mutable accumulator in user code. *)
let mean (data : int list) : float =
  let total = List.fold_left ( + ) 0 data in
  float_of_int total /. float_of_int (List.length data)

(* Median: sort an immutable copy, then pick the middle element(s).
   List.nth gives positional access without mutating the list. *)
let median (data : int list) : float =
  let sorted = List.sort compare data in
  let n = List.length sorted in
  let mid = n / 2 in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted mid)
  else
    let a = List.nth sorted (mid - 1) in
    let b = List.nth sorted mid in
    (float_of_int a +. float_of_int b) /. 2.0

(* Build an association list of (value, frequency) pairs functionally.
   For each value we fold over the existing pairs to either bump an
   existing count or append a fresh pair, always returning a new list. *)
let frequencies (data : int list) : (int * int) list =
  List.fold_left
    (fun acc x ->
      if List.mem_assoc x acc then
        List.map (fun (k, c) -> if k = x then (k, c + 1) else (k, c)) acc
      else
        acc @ [ (x, 1) ])
    [] data

(* Mode: compute frequencies, find the maximum count with fold_left,
   then filter the pairs down to those matching that count. The result
   is sorted so output is deterministic. *)
let mode (data : int list) : int list =
  let freqs = frequencies data in
  let max_count =
    List.fold_left (fun m (_, c) -> if c > m then c else m) 0 freqs
  in
  freqs
  |> List.filter (fun (_, c) -> c = max_count)
  |> List.map (fun (k, _) -> k)
  |> List.sort compare

(* Render an int list as a space separated string without mutation. *)
let string_of_int_list (lst : int list) : string =
  String.concat " " (List.map string_of_int lst)

let () =
  let data = [ 7; 3; 9; 3; 5; 7; 3; 8; 5; 10; 7; 3 ] in
  Printf.printf "Statistics Calculator (OCaml, Functional)\n";
  Printf.printf "=========================================\n";
  Printf.printf "Input data (%d values): %s\n"
    (List.length data) (string_of_int_list data);
  Printf.printf "Sorted data:           %s\n\n"
    (string_of_int_list (List.sort compare data));
  Printf.printf "Mean:   %.2f\n" (mean data);
  Printf.printf "Median: %.2f\n" (median data);
  Printf.printf "Mode:   %s\n"
    (String.concat ", " (List.map string_of_int (mode data)))
