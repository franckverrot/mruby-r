class DataSource
  def initialize
    @bytes = (1543..1546).map do |issue_number|
      issue_file = "./xkcds/#{issue_number}.json"
      content = File.read(issue_file)
      issue = JSON.parse(content)

      transcript = issue["transcript"].
        bytes.
        select { |b| b >= 0x40 && b <= 0x7A }.
        map(&:chr)
    end.flatten.to_enum
  end

  def next
    @bytes.next
  end

  self
end
