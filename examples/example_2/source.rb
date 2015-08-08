class DataSource
  def initialize
    @bytes = (1543..1546).map do |issue_number|
      issue_file = "./xkcds/#{issue_number}.json"
      content = File.read(issue_file)
      issue = JSON.parse(content)

      issue["transcript"].
        bytes.
        select { |b| b.between?(0x41, 0x5A) || b.between?(0x61, 0x7A) }.
        map(&:chr)
    end.flatten.to_enum
  end

  def next
    @bytes.next rescue nil
  end

  self
end
